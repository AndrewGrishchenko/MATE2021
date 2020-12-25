#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <SDL/SDL.h>

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QBuffer>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>

int baudrate = 9600;
int port = 7755;
int current_tab = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);

//    m_joy = SDL_JoystickOpen(SDL_NumJoysticks() - 1);
    m_udp = new QUdpSocket;
    m_inputpacket = new InputPacket;
    m_outputpacket = new OutputPacket;
    is_connected = m_udp->bind(QHostAddress("169.254.101.40"), 5115);

    timer = new QTimer(this);
    timer->setInterval(60);
    timer->start();

    joy_timer = new QTimer(this);
    joy_timer->setInterval(10);
    joy_timer->start();

    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    m_timer->start();

    m_speed_timer = new QTimer(this);
    m_speed_timer->setInterval(20);
    m_speed_timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::func);
    connect(joy_timer, &QTimer::timeout, this, &MainWindow::read_axis);
    connect(m_speed_timer, &QTimer::timeout, this, &MainWindow::countRealSpeed);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::ready_to_read);
    connect(ui->camComboBox,SIGNAL(activated(int)),this,SLOT(camComboBox_event(int)));

    init_cameras();
}



long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long constrain(long x, long min, long max)
{
    if(x > max) return max;
    else if(x < min) return min;
    else return x;
}



//void MainWindow::set_data_to_ui()
//{
//    //set data
//}

int countCameras()
{
   cv::VideoCapture temp_camera;
   int maxTested = 10;
   for (int i = 0; i < maxTested; i++){
     cv::VideoCapture temp_camera(i);
     bool res = (!temp_camera.isOpened());
     temp_camera.release();
     if (res)
     {
       return i;
     }
   }
   return maxTested;
}

void MainWindow::send() {
    m_udp->writeDatagram((char *)(m_outputpacket),sizeof(*m_outputpacket), QHostAddress("169.254.101.39"), 5115);


    //    QByteArray data;
//    data.push_back();
//    data.push_back(output.roll);
//    data.push_back(output.depth);
//    data.push_back(output.pitch);

//    QNetworkDatagram datagram;
//    datagram.setData(data);
//    udpSocket->writeDatagram(data, QHostAddress::Broadcast, port);
//    udpSocket->write(datagram, QHostAddress("164.132.69.65"), port);
}

bool MainWindow::read()
{
    QHostAddress *adress = new QHostAddress("169.254.101.39");
//    QHostAddress *adress = new QHostAddress::Any;
    if(m_udp->hasPendingDatagrams())
    {
        m_udp->readDatagram((char *)(m_inputpacket), sizeof(*m_inputpacket), adress);
        return true;
    }
    else return false;
}

void MainWindow::ready_to_read()
{
    //unparse data from input packet, if read()
    if(read())
    {
//        ui->Status_Label->setText("Ok");
        parseInputPacket();
    }
    //else if(is_connected > -1)ui->Status_Label->setText("Сюда не смотри");
    //else ui->Status_Label->setText("Can't connect to 169.254.101.39");

}

void  MainWindow::fillOutputPacket()
{
    //fill m_outputpacket with data


    m_outputpacket->is_settings = true;

    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->YawKi = float(ui->YawKi_Value->value());
    m_outputpacket->YawKd = float(ui->YawKd_Value->value());
    m_outputpacket->PitchKp = float(ui->PitchKp_Value->value());
    m_outputpacket->PitchKi = float(ui->PitchKi_Value->value());
    m_outputpacket->PitchKd = float(ui->PitchKd_Value->value());
    m_outputpacket->RollKp = float(ui->RollKp_Value->value());
    m_outputpacket->RollKi = float(ui->RollKi_Value->value());
    m_outputpacket->RollKd = float(ui->RollKd_Value->value());
    m_outputpacket->DepthKp = float(ui->DepthKp_Value->value());
    m_outputpacket->DepthKi = float(ui->DepthKi_Value->value());
    m_outputpacket->DepthKd = float(ui->DepthKd_Value->value());
    m_outputpacket->YawToSet = float(ui->YawToSet_Value->value());
    m_outputpacket->PitchToSet = float(ui->PitchToSet_Value->value());
    m_outputpacket->RollToSet = float(ui->RollToSet_Value->value());
    m_outputpacket->DepthToSet = float(ui->DepthToSet_Value->value());
    m_outputpacket->yaw_reg_enable = ui->YawReg_Enabler->isChecked();
    m_outputpacket->pitch_reg_enable = ui->PitchReg_Enabler->isChecked();
    m_outputpacket->roll_reg_enable = ui->RollReg_Enabler->isChecked();
    m_outputpacket->depth_reg_enable = ui->DepthReg_Enabler->isChecked();
}

void MainWindow::parseInputPacket()
{
    //get data from m_inputpacket
//    qDebug() << QString::number(double(m_inputpacket->yaw));
//    qDebug() << m_inputpacket->roll;

    ui->Yaw_Value->setText(QString::number(double(m_inputpacket->yaw)));
    ui->Pitch_Value->setText(QString::number(double(m_inputpacket->pitch)));
    ui->Roll_Value->setText(QString::number(double(m_inputpacket->roll)));
    ui->Depth_Value->setText(QString::number(double(m_inputpacket->depth)));


    //ui->Temperature_Value->setText(QString::number(double(m_inputpacket->temperature)));
    //ui->Core_Value->setText(QString::number(double(m_inputpacket->core)));
}

void MainWindow::func()
{
//    fillOutputPacket(); //fill output packet with data
//    send();             //send this packet
//    while (1) {
////        ready_to_read();
////        send();
//    }


//    SDL_Joystick* gGameController = NULL;

//    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
//    {
//        qDebug() << "SDL could not initialize! SDL Error: %s\n", SDL_GetError();
//    }

//    //  Check for joysticks
//    if( SDL_NumJoysticks() < 1 )
//    {
//        qDebug() << "Warning: No joysticks connected!\n";
//    }
//    else
//    {
//        //Load joystick
//        gGameController = SDL_JoystickOpen(0);
//        if( gGameController == NULL )
//        {
//            qDebug() << "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError();
//        }
//    }

//    cv::VideoCapture cap(0);
//    if (!cap.isOpened()) {
//        qDebug() << "Error camera";
//    }
//    cv::Mat frame;
////    cap >> frame;
//    while (1)
//    {
////        qDebug() << 1;
//        cap >> frame;
////        qDebug() << 2;
//        cv::imshow("frame", frame);
////        qDebug() << 3;
//        cv::waitKey(30);
////        qDebug() << 4;
////        char c = (char)cv::waitKey(25);
////        if (c == 27) {
////            break;
//    }

}

void MainWindow::countRealSpeed()
{
    if(ui->MaxSpeed_Value->value() > m_real_speed)
    {
        m_real_speed++;
    }
    else
    {
        m_real_speed = ui->MaxSpeed_Value->value();
    }
    ui->RealSpd_Value->setNum(int(m_real_speed));
    ui->RealSpd_Value2->setNum(int(m_real_speed));
}

void MainWindow::read_axis()
{
    SDL_Joystick* joy = SDL_JoystickOpen(SDL_NumJoysticks() - 1);
    SDL_JoystickUpdate();

    m_outputpacket->axis_X = constrain(map(SDL_JoystickGetAxis(joy, 0) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
    m_outputpacket->axis_Y = -constrain(-map(SDL_JoystickGetAxis(joy, 1) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
    m_outputpacket->axis_Z = constrain(map(SDL_JoystickGetAxis(joy, 2) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
    m_outputpacket->axis_W = constrain(map(SDL_JoystickGetAxis(joy, 3) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
    m_outputpacket->manipulator_rotate = constrain(map(SDL_JoystickGetAxis(joy, 4) + 1, -32768, 32767, -1, 1), -1, 1);

    if(SDL_JoystickGetButton(joy, 1) == 1) m_outputpacket->manipulator_grab = 1;
    else if(SDL_JoystickGetButton(joy, 0) == 1) m_outputpacket->manipulator_grab = -1;
    else m_outputpacket->manipulator_grab = 0;
    if(SDL_JoystickGetHat(joy, 0) == 1) m_outputpacket->camera_rotate = 1;
    else if(SDL_JoystickGetHat(joy, 0) == 4) m_outputpacket->camera_rotate = -1;
    else m_outputpacket->camera_rotate = 0;

    for(int i = 0; i < 8; i++) // заполняем кнопки (0 и 1 заняты маником)
    {
        m_outputpacket->buttons[i] = SDL_JoystickGetButton(joy, i + 2);
    }
    if(m_outputpacket->buttons[4] == 1)
    {
        ui->MaxSpeed_Value->setValue(25);
        ui->MaxSpeed_Value2->setValue(25);
    }
    if(m_outputpacket->buttons[3] == 1)
    {
        ui->MaxSpeed_Value->setValue(50);
        ui->MaxSpeed_Value2->setValue(50);
    }
    if(m_outputpacket->buttons[2] == 1)
    {
        ui->MaxSpeed_Value->setValue(75);
        ui->MaxSpeed_Value2->setValue(75);
    }

    ui->X_Value->setNum(m_outputpacket->axis_X);
    ui->Y_Value->setNum(-m_outputpacket->axis_Y);
    ui->Z_Value->setNum(m_outputpacket->axis_Z);
    ui->W_Value->setNum(m_outputpacket->axis_W);
    ui->W_Value->setNum(m_outputpacket->axis_W);
    ui->T_Value->setNum(m_outputpacket->manipulator_rotate);
    ui->Grabber_Value->setNum(m_outputpacket->manipulator_grab);
    ui->Button_3_Value->setNum(m_outputpacket->buttons[0]);
    ui->Button_4_Value->setNum(m_outputpacket->buttons[1]);
    ui->Button_5_Value->setNum(m_outputpacket->buttons[2]);
    ui->Button_6_Value->setNum(m_outputpacket->buttons[3]);
    ui->Button_7_Value->setNum(m_outputpacket->buttons[4]);
    ui->Button_8_Value->setNum(m_outputpacket->buttons[5]);
    ui->Button_9_Value->setNum(m_outputpacket->buttons[6]);
    ui->Button_10_Value->setNum(m_outputpacket->buttons[7]);
    ui->Camera_Value->setNum(m_outputpacket->camera_rotate);
    ui->Mic_Spd_Value->setNum(micro_speed);
    ui->Smatyvolka_Value->setNum(m_outputpacket->smatyvalka);

    if(is_autosend)
    {
        fillOutputPacket();
        send();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == 83) m_outputpacket->m_micro_speed = 0;
    else if(key == 83) m_outputpacket->m_micro_speed = 0;
    if(key == 65) m_outputpacket->smatyvalka = 0;
    else if(key == 65) m_outputpacket->smatyvalka = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    //std::cout <<key<<std::endl;
    if(key == 81)
    {
        micro_speed -= 10;
        micro_speed = constrain(micro_speed, 0, 100);
    }
    if(key == 69)
    {
        micro_speed += 10;
        micro_speed = constrain(micro_speed, 0, 100);
    }
    if(key == 87) m_outputpacket->m_micro_speed = micro_speed;
    else if(key == 83) m_outputpacket->m_micro_speed = -micro_speed;
    else m_outputpacket->m_micro_speed = 0;
    if(key == 70) m_outputpacket->m_micro_led = 0;
    if(key == 82) m_outputpacket->m_micro_led = 1;
    if(key == 65) m_outputpacket->smatyvalka = -1;
    else if(key == 68) m_outputpacket->smatyvalka = 1;
    else m_outputpacket->smatyvalka = 0;
}

void MainWindow::init_cameras()
{
    ui->camComboBox->addItem("None");
    int count = countCameras();
    for (int i = 0; i < count; i++)
    {
        ui->camComboBox->addItem("Cam " + QString::number(i + 1));
    }
}

void MainWindow::on_Update_Button_clicked()
{
    cap.release();
    ui->camComboBox->clear();
    init_cameras();
}

void MainWindow::camComboBox_event(int index)
{
    if (index == 0)
    {
        cap.release();
        ui->frame->clear();
        ui->frame2->clear();
    }
    else
    {
        cap.open(index-1);
        if (!cap.isOpened()) {
            qDebug() << "Error camera";
        }

        img_timer = new QTimer(this);
        connect(img_timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
        img_timer->start(20);
    }
}

void MainWindow::test()
{
    cap.open(0);
    if (!cap.isOpened()) {
        qDebug() << "Error camera";
    }

    img_timer = new QTimer(this);
    connect(img_timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    img_timer->start(20);
}

void MainWindow::processFrameAndUpdateGUI()
{
    cv::Mat originalImage;
    cap.read(originalImage);

    if (originalImage.empty() == true)
    {
        return;
    }

    cv::cvtColor(originalImage, originalImage, cv::COLOR_BGR2RGB);

    QImage qOriginalImage((uchar*)originalImage.data, originalImage.cols,
    originalImage.rows, originalImage.step, QImage::Format_RGB888);   

    switch (current_tab)
    {
        case 0:
            ui->frame->setPixmap(QPixmap::fromImage(qOriginalImage));
            ui->frame->setScaledContents( true );
            ui->frame->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            break;
        case 1:
            ui->frame2->setPixmap(QPixmap::fromImage(qOriginalImage));
            ui->frame2->setScaledContents( true );
            ui->frame2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            break;
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
//    qDebug() << "tab No" << index;
    current_tab = index;
    switch (index)
    {
        case 0:
            //init all cameras
            //and put it in camComboBox1

            //init opencv camera and put it in frame1
            break;
        case 1:
            //init all cameras
            //and put it in camComboBox2

            //init opencv camera and put it in frame2
            break;
    }
}

void MainWindow::on_baudrate9600RadioButton_clicked()
{
    baudrate = 9600;
}

void MainWindow::on_baudrate115200RadioButton_clicked()
{
    baudrate = 115200;
}

void MainWindow::on_startCOMButton_clicked()
{
    //connect with microROV on COMPort
    //ui->COMPortLineEdit->text().toInt();
    //and with baudrate "baudrate"

    //retrieve data from microROV and write it to "..." labels
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_auto_send_stateChanged(int arg1)
{
    is_autosend = arg1;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        QPixmap bkgnd(":/images/anime.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
//        this->setPalette(palette);
//        ui->tabWidget->setPalette(palette);
    }
    else
    {
        QPixmap bkgnd(":/images/white.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
//        this->setPalette(palette);
//        ui->tabWidget->setPalette(palette);
    }
    //Qt сказал не будет аниме девочки >_<
}

void MainWindow::on_Load_Button_clicked()
{
    QFileDialog dialog;
    QFile file(dialog.getOpenFileName());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    double ui_data[12] = {0};
    for(int idx = 0; !in.atEnd(); idx++)
    {
        QString line = in.readLine();
        int i = 0;
        for(i = 0; i < line.size(); i++)
        {
            if(line.at(i) == '=') break;
        }
        QString data;
        for(i = i + 2; i < line.size(); i++)
        {
            data += line.at(i);
        }
        ui_data[idx] = data.toDouble();
    }
    ui->YawKp_Value->setValue(ui_data[0]);
    ui->YawKi_Value->setValue(ui_data[1]);
    ui->YawKd_Value->setValue(ui_data[2]);
    ui->PitchKp_Value->setValue(ui_data[3]);
    ui->PitchKi_Value->setValue(ui_data[4]);
    ui->PitchKd_Value->setValue(ui_data[5]);
    ui->RollKp_Value->setValue(ui_data[6]);
    ui->RollKi_Value->setValue(ui_data[7]);
    ui->RollKd_Value->setValue(ui_data[8]);
    ui->DepthKp_Value->setValue(ui_data[9]);
    ui->DepthKi_Value->setValue(ui_data[10]);
    ui->DepthKd_Value->setValue(ui_data[11]);
}

void MainWindow::on_Save_Button_clicked()
{
    QFileDialog dialog;
    QFile out(dialog.getSaveFileName() + ".txt");
    out.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&out);
    stream.setCodec("UTF-8");
    fillOutputPacket();

    stream << "YawKp = " << m_outputpacket->YawKp << '\n';
    stream << "YawKi = " << m_outputpacket->YawKi << '\n';
    stream << "YawKd = " << m_outputpacket->YawKd << '\n';
    stream << "PitchKp = " << m_outputpacket->PitchKp << '\n';
    stream << "PitchKi = " << m_outputpacket->PitchKi << '\n';
    stream << "PitchKd = " << m_outputpacket->PitchKd << '\n';
    stream << "RollKp = " << m_outputpacket->RollKp << '\n';
    stream << "RollKi = " << m_outputpacket->RollKi << '\n';
    stream << "RollKd = " << m_outputpacket->RollKd << '\n';
    stream << "DepthKp = " << m_outputpacket->DepthKp << '\n';
    stream << "DepthKi = " << m_outputpacket->DepthKi << '\n';
    stream << "DepthKd = " << m_outputpacket->DepthKd << '\n';

    out.close();
}





void MainWindow::on_YawReg_Enabler2_clicked()
{
    ui->YawReg_Enabler->setChecked(ui->YawReg_Enabler2->isChecked());
}
void MainWindow::on_PitchReg_Enabler2_clicked()
{
    ui->PitchReg_Enabler->setChecked(ui->PitchReg_Enabler2->isChecked());
}
void MainWindow::on_RollReg_Enabler2_clicked()
{
    ui->RollReg_Enabler->setChecked(ui->RollReg_Enabler2->isChecked());
}
void MainWindow::on_DepthReg_Enabler2_clicked()
{
    ui->DepthReg_Enabler->setChecked(ui->DepthReg_Enabler2->isChecked());
}
void MainWindow::on_YawReg_Enabler_clicked()
{
    ui->YawReg_Enabler2->setChecked(ui->YawReg_Enabler->isChecked());
}
void MainWindow::on_PitchReg_Enabler_clicked()
{
    ui->PitchReg_Enabler2->setChecked(ui->PitchReg_Enabler->isChecked());
}
void MainWindow::on_RollReg_Enabler_clicked()
{
    ui->RollReg_Enabler2->setChecked(ui->RollReg_Enabler->isChecked());
}
void MainWindow::on_DepthReg_Enabler_clicked()
{
    ui->DepthReg_Enabler2->setChecked(ui->DepthReg_Enabler->isChecked());
}
