#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <SDL/SDL.h>
#include "customlabel.h"

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


    num_img = 0;
    imgs_widths = 0;


    ui->hue_min_slider->setMaximum(255);
    ui->hue_max_slider->setMaximum(255);
    ui->sat_min_slider->setMaximum(255);
    ui->sat_max_slider->setMaximum(255);
    ui->val_min_slider->setMaximum(255);
    ui->val_max_slider->setMaximum(255);

    ui->hue_max_slider->setValue(255);
    ui->sat_max_slider->setValue(255);
    ui->val_max_slider->setValue(255);


    map_img = createGrid();
    map_img.copyTo(old_map_img);
    QPixmap map_pixmap;
    const uchar *qImageBuffer = (const uchar*)map_img.data;
    QImage map_image(qImageBuffer, map_img.cols, map_img.rows, map_img.step, QImage::Format_RGB888);
    map_pixmap = QPixmap::fromImage(map_image.rgbSwapped());
    ui->Map_photoLabel->setPixmap(map_pixmap);


    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);

//    m_joy = SDL_JoystickOpen(SDL_NumJoysticks() - 1);
    m_udp = new QUdpSocket;
    m_inputpacket = new InputPacket;
    m_outputpacket = new OutputPacket;
    is_connected = m_udp->bind(QHostAddress("169.254.111.189"), 5115);

    timer = new QTimer(this);
    timer->setInterval(60);
    timer->start();

    joy_timer = new QTimer(this);
    joy_timer->setInterval(50);
    joy_timer->start();

    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    m_timer->start();

    m_speed_timer = new QTimer(this);
    m_speed_timer->setInterval(10);
    m_speed_timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::func);
    connect(joy_timer, &QTimer::timeout, this, &MainWindow::read_axis);
    connect(m_speed_timer, &QTimer::timeout, this, &MainWindow::countRealSpeed);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::ready_to_read);
    connect(ui->camComboBox,SIGNAL(activated(int)),this,SLOT(camComboBox_event(int)));
    connect(ui->Map_photoLabel, &CustomLabel::mousePressed, this, &MainWindow::processMap);

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
    //qDebug() << sizeof (m_outputpacket);
    m_udp->writeDatagram((char *)(m_outputpacket),sizeof(*m_outputpacket), QHostAddress("169.254.111.189"), 5115);


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
    QHostAddress *adress = new QHostAddress("169.254.111.189");
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


    //m_outputpacket->is_settings = true;

    m_outputpacket->m_YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->m_YawKp = float(ui->YawKp_Value->value());
    m_outputpacket->m_YawKi = float(ui->YawKi_Value->value());
    m_outputpacket->m_YawKd = float(ui->YawKd_Value->value());
    m_outputpacket->m_PitchKp = float(ui->PitchKp_Value->value());
    m_outputpacket->m_PitchKi = float(ui->PitchKi_Value->value());
    m_outputpacket->m_PitchKd = float(ui->PitchKd_Value->value());
    m_outputpacket->m_RollKp = float(ui->RollKp_Value->value());
    m_outputpacket->m_RollKi = float(ui->RollKi_Value->value());
    m_outputpacket->m_RollKd = float(ui->RollKd_Value->value());
    m_outputpacket->m_DepthKp = float(ui->DepthKp_Value->value());
    m_outputpacket->m_DepthKi = float(ui->DepthKi_Value->value());
    m_outputpacket->m_DepthKd = float(ui->DepthKd_Value->value());
    m_outputpacket->m_YawToSet = float(ui->YawToSet_Value->value());
    m_outputpacket->m_PitchToSet = float(ui->PitchToSet_Value->value());
    m_outputpacket->m_RollToSet = float(ui->RollToSet_Value->value());
    m_outputpacket->m_DepthToSet = float(ui->DepthToSet_Value->value());
    m_outputpacket->m_yaw_reg_enable = ui->YawReg_Enabler->isChecked();
    m_outputpacket->m_pitch_reg_enable = ui->PitchReg_Enabler->isChecked();
    m_outputpacket->m_roll_reg_enable = ui->RollReg_Enabler->isChecked();
    m_outputpacket->m_depth_reg_enable = ui->DepthReg_Enabler->isChecked();
    m_outputpacket->m_micro_speed = micro_speed;
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
    if(m_axis_x > m_axis_x_old)
    {
        m_axis_x_old++;
        m_outputpacket->axisX_p = m_axis_x_old;
    }
    else if(m_axis_x < m_axis_x_old)
    {
        m_axis_x_old--;
        m_outputpacket->axisX_p = m_axis_x_old;
    }
    if(m_axis_y > m_axis_y_old)
    {
        m_axis_y_old++;
        m_outputpacket->axisY_p = m_axis_y_old;
    }
    else if(m_axis_y < m_axis_y_old)
    {
        m_axis_y_old--;
        m_outputpacket->axisY_p = m_axis_y_old;
    }
    if(m_axis_z > m_axis_z_old)
    {
        m_axis_z_old++;
        m_outputpacket->axisZ_p = m_axis_z_old;
    }
    else if(m_axis_z < m_axis_z_old)
    {
        m_axis_z_old--;
        m_outputpacket->axisZ_p = m_axis_z_old;
    }
    if(m_axis_w > m_axis_w_old)
    {
        m_axis_w_old++;
        m_outputpacket->axisW_p = m_axis_w_old;
    }
    else if(m_axis_w < m_axis_w_old)
    {
        m_axis_w_old--;
        m_outputpacket->axisW_p = m_axis_w_old;
    }
//    if(ui->MaxSpeed_Value->value() > m_real_speed)
//    {
//        m_real_speed++;
//    }
//    else
//    {
//        m_real_speed = ui->MaxSpeed_Value->value();
//    }
    ui->RealSpd_Value->setNum(int(m_real_speed));
    ui->RealSpd_Value2->setNum(int(m_real_speed));
}

void MainWindow::read_axis()
{
    SDL_Joystick* joy = SDL_JoystickOpen(SDL_NumJoysticks() - 1);
    SDL_JoystickUpdate();

    m_axis_x = map(SDL_JoystickGetAxis(joy, 0) + 1, -32768, 32767, -ui->MaxSpeed_Value->value(), ui->MaxSpeed_Value->value());
    m_axis_y = -map(SDL_JoystickGetAxis(joy, 1) + 1, -32768, 32767, -ui->MaxSpeed_Value->value(), ui->MaxSpeed_Value->value());
    m_axis_z = map(SDL_JoystickGetAxis(joy, 2) + 1, -32768, 32767, -ui->MaxSpeed_Value->value(), ui->MaxSpeed_Value->value());
    m_axis_w = map(SDL_JoystickGetAxis(joy, 3) + 1, -32768, 32767, -ui->MaxSpeed_Value->value(), ui->MaxSpeed_Value->value());
    //qDebug() << m_axis_x << '\n';
//    m_outputpacket->axisX_p = constrain(map(SDL_JoystickGetAxis(joy, 0) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
//    m_outputpacket->axisY_p = -constrain(-map(SDL_JoystickGetAxis(joy, 1) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
//    m_outputpacket->axisZ_p = constrain(map(SDL_JoystickGetAxis(joy, 2) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
//    m_outputpacket->axisW_p = constrain(map(SDL_JoystickGetAxis(joy, 3) + 1, -32768, 32767, -100 * 0.01 * m_real_speed, 100 * 0.01 * m_real_speed), -m_real_speed, m_real_speed);
    //m_outputpacket->m_smatyvalka_value = constrain(map(SDL_JoystickGetAxis(joy, 4) + 1, -32768, 32767, -1, 1), -1, 1);
    //qDebug() << ui->MaxSpeed_Value->text() << m_real_speed;
    //qDebug() << ui->MaxSpeed_Value->text() << m_real_speed << m_axis_w << m_outputpacket->axisW_p << m_axis_w_old;
        qDebug() << (int)m_outputpacket->axisX_p << (int)m_outputpacket->axisY_p << (int)m_outputpacket->axisZ_p << (int)m_outputpacket->axisW_p << '\n';
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
        ui->MaxSpeed_Value->setValue(45);
        ui->MaxSpeed_Value2->setValue(40);
    }
    if(m_outputpacket->buttons[3] == 1)
    {
        ui->MaxSpeed_Value->setValue(60);
        ui->MaxSpeed_Value2->setValue(60);
    }
    if(m_outputpacket->buttons[2] == 1)
    {
        ui->MaxSpeed_Value->setValue(85);
        ui->MaxSpeed_Value2->setValue(85);
    }

    ui->X_Value->setNum(m_outputpacket->axisX_p);
    ui->Y_Value->setNum(-m_outputpacket->axisY_p);
    ui->Z_Value->setNum(m_outputpacket->axisZ_p);
    ui->W_Value->setNum(m_outputpacket->axisY_p);
//    ui->T_Value->setNum(m_outputpacket->manipulator_rotate);
//    ui->Grabber_rotate->setNum(m_outputpacket->manipulator_rotate);
    ui->Smatyvolka_Value->setNum(m_outputpacket->m_smatyvalka_value);
    ui->Grabber_grab->setNum(m_outputpacket->manipulator_grab);
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
    ui->Smatyvolka_Value->setNum(m_outputpacket->m_smatyvalka_value);

    if(is_autosend)
    {
        fillOutputPacket();
        send();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    //??

//    int key = event->key();
//    if(key == 83) m_outputpacket->m_micro_speed = 0;
//    else if(key == 83) m_outputpacket->m_micro_speed = 0;
//    if(key == 65) m_outputpacket->smatyvalka = 0;
//    else if(key == 65) m_outputpacket->smatyvalka = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    char c = char(event->key());
    switch (c)
    {
        case 'F':
            micro_speed = 0;
            break;
        case 'W':
            if (micro_speed < 0) micro_speed *= -1;
            break;
        case 'A':
            micro_speed -= 10;
            break;
        case 'S':
            if (micro_speed > 0) micro_speed *= -1;
            break;
        case 'D':
           micro_speed += 10;
           break;
//        case 'Z':
//           m_outputpacket->smatyvalka = -1;
//           break;
//        case 'X':
//           m_outputpacket->smatyvalka = 1;
//           break;
//        case 'C':
//           m_outputpacket->smatyvalka = 0;
//           break;
    }


    //??

//    int key = event->key();
//    //std::cout <<key<<std::endl;
//    if(key == 81)
//    {
//        micro_speed -= 10;
//        micro_speed = constrain(micro_speed, 0, 100);
//    }
//    if(key == 69)
//    {
//        micro_speed += 10;
//        micro_speed = constrain(micro_speed, 0, 100);
//    }
//    if(key == 87) m_outputpacket->m_micro_speed = micro_speed;
//    else if(key == 83) m_outputpacket->m_micro_speed = -micro_speed;
//    else m_outputpacket->m_micro_speed = 0;
//    if(key == 70) m_outputpacket->m_micro_led = 0;
//    if(key == 82) m_outputpacket->m_micro_led = 1;
//    if(key == 65) m_outputpacket->smatyvalka = -1;
//    else if(key == 68) m_outputpacket->smatyvalka = 1;
//    else m_outputpacket->smatyvalka = 0;
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
        ui->Subway_camLabel->clear();
    }
    else
    {
        camera_index = index - 1;
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
    ui->Subway_camLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
    ui->Subway_camLabel->setScaledContents(true);
    ui->Subway_camLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
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

    stream << "YawKp = " << m_outputpacket->m_YawKp << '\n';
    stream << "YawKi = " << m_outputpacket->m_YawKi << '\n';
    stream << "YawKd = " << m_outputpacket->m_YawKd << '\n';
    stream << "PitchKp = " << m_outputpacket->m_PitchKp << '\n';
    stream << "PitchKi = " << m_outputpacket->m_PitchKi << '\n';
    stream << "PitchKd = " << m_outputpacket->m_PitchKd << '\n';
    stream << "RollKp = " << m_outputpacket->m_RollKp << '\n';
    stream << "RollKi = " << m_outputpacket->m_RollKi << '\n';
    stream << "RollKd = " << m_outputpacket->m_RollKd << '\n';
    stream << "DepthKp = " << m_outputpacket->m_DepthKp << '\n';
    stream << "DepthKi = " << m_outputpacket->m_DepthKi << '\n';
    stream << "DepthKd = " << m_outputpacket->m_DepthKd << '\n';

    out.close();
}

//HSV
void MainWindow::hsv_setting(std::vector<int> hsv_min, std::vector<int> hsv_max)
{
    ui->hue_min_label->setText("Hue Min: 0");
    ui->sat_min_label->setText("Saturaion Min: 0");
    ui->val_min_label->setText("Value Min: 0");
    ui->hue_max_label->setText("Hue Max: 255");
    ui->sat_max_label->setText("Saturation Max: 255");
    ui->val_max_label->setText("Value Max: 255");

    if (camera_index == -1)
    {
        qDebug() << "Select camera";
        stop_hsv = true;
    }
    cv::Mat img;

    while (!stop_hsv && !dest)
    {
//        img = cv::imread("C://Users/andre/Desktop/test1.png");
        cap.read(img);

        cv::Mat img_hsv;
        cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
        cv::Mat mask;
        cv::inRange(img_hsv, cv::Scalar(hue_min_label, sat_min_label, val_min_label), cv::Scalar(hue_max_label, sat_max_label, val_max_label), mask);
        cv::Mat frame;
        cv::bitwise_or(img, img, frame, mask);

//        cv::imshow("img", img);
//        cv::imshow("img_hsv", img_hsv);
        cv::imshow("mask", mask);
        cv::imshow("frame", frame);
        cv::waitKey(50);

        qDebug() << "hsv_min" << hue_min_label << sat_min_label << val_min_label << "hsv_max" << hue_max_label << sat_max_label << val_max_label;
    }
    cv::destroyAllWindows();
//    cv::destroyWindow("mask");
//    cv::destroyWindow("frame");
}




//SUBWAY
void MainWindow::on_Subway_ShotButton_clicked()
{
    cv::Mat img;
    cap.read(img);

    if (img.empty() == true)
    {
        qDebug() << "shotButton error";
        return;
    }

    //some raspoznavaniye

    num_img += 1;
    if (num_img == 5)
    {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        cv::Mat blank1(img.rows, imgs_widths, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::hconcat(blank1, img, secondImg);

        cv::Mat blank2(secondImg.rows, firstImg.cols - secondImg.cols, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::hconcat(secondImg, blank2, secondImg);

        cv::vconcat(secondImg, firstImg, finalImg);

        QImage qOriginalImage((uchar*)finalImg.data, finalImg.cols,
        finalImg.rows, finalImg.step, QImage::Format_RGB888);

        ui->Subway_photoLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
        ui->Subway_photoLabel->setScaledContents(true);
        ui->Subway_photoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else if (num_img == 1)
    {
        firstImg = img;
        imgs_widths += firstImg.cols;

        cv::cvtColor(firstImg, firstImg, cv::COLOR_BGR2RGB);

        QImage qOriginalImage((uchar*)firstImg.data, firstImg.cols,
        firstImg.rows, firstImg.step, QImage::Format_RGB888);


        ui->Subway_photoLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
        ui->Subway_photoLabel->setScaledContents(true);
        ui->Subway_photoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else if (num_img < 5)
    {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

//        cv::imshow("img", img);
//        cv::imshow("firstImg", firstImg);

        cv::hconcat(firstImg, img, firstImg);

//        cv::cvtColor(firstImg, firstImg, cv::COLOR_BGR2RGB);

        QImage qOriginalImage((uchar*)firstImg.data, firstImg.cols,
        firstImg.rows, firstImg.step, QImage::Format_RGB888);


        ui->Subway_photoLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
        ui->Subway_photoLabel->setScaledContents(true);
        ui->Subway_photoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else num_img -= 1;
}
void MainWindow::on_Subway_ClearButton_clicked()
{
    firstImg.release();
    secondImg.release();
    finalImg.release();
    num_img = 0;
    imgs_widths = 0;
    ui->Subway_photoLabel->clear();
}
void MainWindow::on_Subway_ctrlzButton_clicked()
{
    if (num_img > 0)
    {
        if (num_img == 5)
        {
            secondImg.release();
            finalImg.release();


//            int width = firstImg.cols;
//            int height = firstImg.rows/2;
//            cv::Rect ROI(0, 0, width, height);
//            cv::Mat ctrlz_firstImg(firstImg, ROI);

//            cv::imshow("firstImg", firstImg);
//            cv::imshow("ctrlz", ctrlz_firstImg);

//            firstImg = ctrlz_firstImg.clone();

            QImage qOriginalImage((uchar*)firstImg.data, firstImg.cols,
            firstImg.rows, firstImg.step, QImage::Format_RGB888);


            ui->Subway_photoLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
            ui->Subway_photoLabel->setScaledContents(true);
            ui->Subway_photoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            num_img -= 1;
        }
        else if (num_img == 1)
        {
            firstImg.release();
            secondImg.release();
            finalImg.release();
            num_img = 0;
            imgs_widths = 0;
            ui->Subway_photoLabel->clear();
        }
        else if (num_img < 5)
        {
            cv::Rect ROI(0, 0, firstImg.cols/num_img * (num_img - 1), firstImg.rows);
            cv::Mat ctrlz_firstImg(firstImg, ROI);

//            cv::imshow("firstImg", firstImg);
//            cv::imshow("ctrlz", ctrlz_firstImg);

            firstImg = ctrlz_firstImg.clone();

            QImage qOriginalImage((uchar*)firstImg.data, firstImg.cols,
            firstImg.rows, firstImg.step, QImage::Format_RGB888);


            ui->Subway_photoLabel->setPixmap(QPixmap::fromImage(qOriginalImage));
            ui->Subway_photoLabel->setScaledContents(true);
            ui->Subway_photoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            num_img -= 1;
        }
    }
}




//MAP
cv::Mat MainWindow::createGrid()
{
    cv::Mat img(cv::Size(900, 300), CV_8UC3, cv::Scalar(255, 255, 255));
    for (int i = 1; i < 10; i++)
    {
        cv::line(img, cv::Point(i * 100, 0), cv::Point(i * 100, 300), cv::Scalar(0, 0, 0));
    }
    for(int i = 1; i < 4; i++)
    {
        cv::line(img, cv::Point(0, i * 100), cv::Point(900, i * 100), cv::Scalar(0, 0, 0));
    }
    return img;
}

void MainWindow::processMap()
{
    map_img.copyTo(old_map_img);

    int x = ui->Map_photoLabel->xpos;
    int y = ui->Map_photoLabel->ypos;
    int width = ui->Map_photoLabel->width();
    int height = ui->Map_photoLabel->height();
    float xK = (float)map_img.cols / (float)width;
    float yK = (float)map_img.rows / (float)height;
    int num_width = (map_img.cols / 9);
    int num_height = (map_img.rows / 3);
    int numX = x * xK / num_width + 1;
    int numY = y * yK / num_height + 1;

    switch (shape_num)
    {
    //        cv::circle(img, cv::Point(x * xK, y * yK), 5, cv::Scalar(0, 0, 0));
        case 1:
            cv::circle(map_img, cv::Point((numX * num_width) - (num_width / 2), (numY * num_height) - (num_height / 2)), (num_width / 2 * 0.75), CV_RGB(0, 0, 255), 3);
            break;
        case 2:
            cv::circle(map_img, cv::Point((numX * num_width) - (num_width / 2), (numY * num_height) - (num_height / 2)), (num_width / 2 * 0.75), CV_RGB(255, 255, 0), 3);
            break;
        case 3:
            cv::ellipse(map_img, cv::Point(numX * num_width, (numY * num_height) - (num_height / 2)), cv::Size(num_width * 0.75, num_height / 2 * 0.75), 0, 0, 360, CV_RGB(255, 0, 0), 3);
            break;
        case 4:
            cv::circle(map_img, cv::Point((numX * num_width) - (num_width / 2), (numY * num_height) - (num_height / 2)), (num_width / 2 * 0.75), CV_RGB(0, 255, 0), 3);
            break;
    }

    QPixmap map_pixmap;
    const uchar *qImageBuffer = (const uchar*)map_img.data;
    QImage map_image(qImageBuffer, map_img.cols, map_img.rows, map_img.step, QImage::Format_RGB888);
    map_pixmap = QPixmap::fromImage(map_image.rgbSwapped());

    ui->Map_photoLabel->setPixmap(map_pixmap);
}
void MainWindow::on_Map_CtrlzButton_clicked()
{
    old_map_img.copyTo(map_img);
    QPixmap map_pixmap;
    const uchar *qImageBuffer = (const uchar*)map_img.data;
    QImage map_image(qImageBuffer, map_img.cols, map_img.rows, map_img.step, QImage::Format_RGB888);
    map_pixmap = QPixmap::fromImage(map_image.rgbSwapped());
    ui->Map_photoLabel->setPixmap(map_pixmap);
}
void MainWindow::on_Map_ClearButton_clicked()
{
    map_img = createGrid();
    map_img.copyTo(old_map_img);
    QPixmap map_pixmap;
    const uchar *qImageBuffer = (const uchar*)map_img.data;
    QImage map_image(qImageBuffer, map_img.cols, map_img.rows, map_img.step, QImage::Format_RGB888);
    map_pixmap = QPixmap::fromImage(map_image.rgbSwapped());
    ui->Map_photoLabel->setPixmap(map_pixmap);
}



//MUSSELS
cv::Mat MainWindow::findCircles()
{
    while (!stop_mussels && !dest)
    {
//        cap.read(img);
        cv::Mat img = cv::imread("D://some.png");
//        cv::Mat newimg = findCircles();
//        cv::imshow("img", img);

    //    img = imread("circles.png", cv::IMREAD_COLOR);

        cv::Mat newimg;
        img.copyTo(newimg);
        cv::Mat gray;
        cv::cvtColor(newimg, gray, cv::COLOR_BGR2GRAY);
        cv::Mat img_blur;
        cv::medianBlur(gray, img_blur, 5);
        std::vector<cv::Vec3f>  circles;
        cv::HoughCircles(img_blur, circles, cv::HOUGH_GRADIENT, 1, newimg.rows/64, 200, 10, 5, 30);
//        cv::HoughCircles(img_blur, circles, cv::HOUGH_GRADIENT, 2.8, 50, 10, 30, 5, 40);
//        qDebug() << newimg.rows << newimg.rows/64;
        for(size_t i=0; i<circles.size(); i++)
        {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            cv::circle(newimg, center, radius, cv::Scalar(0, 0, 0), 2, 8, 0);
        }
//        return newimg;

        cv::imshow("img", img);
        cv::imshow("newimg", newimg);
        cv::waitKey(50);
    }
    cv::destroyAllWindows();
}
void MainWindow::on_mussels_StartButton_clicked()
{
    stop_mussels = false;
    findCircles();
}
void MainWindow::on_mussels_StopButton_clicked()
{
    stop_mussels = true;
}



//MAP THINGS
void MainWindow::on_Map_bCircleRB_clicked()
{
    shape_num = 1;
}
void MainWindow::on_Map_yCircleRB_clicked()
{
    shape_num = 2;
}
void MainWindow::on_Map_rEllipseRB_clicked()
{
    shape_num = 3;
}
void MainWindow::on_Map_gCircleRB_clicked()
{
    shape_num = 4;
}





//HSV THINGS
void MainWindow::on_start_HSV_Button_clicked()
{
    stop_hsv = false;
    hsv_setting(hsv_min, hsv_max);
}
void MainWindow::on_stop_HSV_Button_clicked()
{
    stop_hsv = true;
}
void MainWindow::on_hue_min_slider_actionTriggered(int action)
{
    hue_min_label = ui->hue_min_slider->value();
    ui->hue_min_label->setText("Hue Min: " + QString::number(hue_min_label));
}
void MainWindow::on_hue_max_slider_actionTriggered(int action)
{
    hue_max_label = ui->hue_max_slider->value();
    ui->hue_max_label->setText("Hue Max: " + QString::number(hue_max_label));
}
void MainWindow::on_sat_min_slider_actionTriggered(int action)
{
    sat_min_label = ui->sat_min_slider->value();
    ui->sat_min_label->setText("Saturation Min: " + QString::number(sat_min_label));
}
void MainWindow::on_sat_max_slider_actionTriggered(int action)
{
    sat_max_label = ui->sat_max_slider->value();
    ui->sat_max_label->setText("Saturation Max: " + QString::number(sat_max_label));
}
void MainWindow::on_val_min_slider_actionTriggered(int action)
{
    val_min_label = ui->val_min_slider->value();
    ui->val_min_label->setText("Value Min: " + QString::number(val_min_label));
}
void MainWindow::on_val_max_slider_actionTriggered(int action)
{
    val_max_label = ui->val_max_slider->value();
    ui->val_max_label->setText("Value Max: " + QString::number(val_max_label));
}



//ENABLERS
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


//SOME
void MainWindow::closeEvent (QCloseEvent *event)
{
    dest = true;
}
MainWindow::~MainWindow()
{
    delete ui;
}
