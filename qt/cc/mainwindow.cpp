#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <SDL.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <QUdpSocket>
#include <QNetworkDatagram>



int baudrate = 9600;
int port = 7755;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_joy = SDL_JoystickOpen(SDL_NumJoysticks() - 1);
    m_udp = new QUdpSocket;
    m_inputpacket = new InputPacket;
    m_outputpacket = new OutputPacket;
    is_connected = m_udp->bind(QHostAddress("169.254.101.40"), 5115);

    QTimer *timer = new QTimer(this);
    timer->setInterval(60);
    timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::func);

}


//void MainWindow::set_data_to_ui()
//{
//    //set data
//}

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
    QHostAddress *adress = new QHostAddress("169.254.101.40");
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


//    m_outputpacket->is_settings = true;

//    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
//    m_outputpacket->YawKp = float(ui->YawKp_Value->value());
//    m_outputpacket->YawKi = float(ui->YawKi_Value->value());
//    m_outputpacket->YawKd = float(ui->YawKd_Value->value());
//    m_outputpacket->PitchKp = float(ui->PitchKp_Value->value());
//    m_outputpacket->PitchKi = float(ui->PitchKi_Value->value());
//    m_outputpacket->PitchKd = float(ui->PitchKd_Value->value());
//    m_outputpacket->RollKp = float(ui->RollKp_Value->value());
//    m_outputpacket->RollKi = float(ui->RollKi_Value->value());
//    m_outputpacket->RollKd = float(ui->RollKd_Value->value());
//    m_outputpacket->DepthKp = float(ui->DepthKp_Value->value());
//    m_outputpacket->DepthKi = float(ui->DepthKi_Value->value());
//    m_outputpacket->DepthKd = float(ui->DepthKd_Value->value());
//    m_outputpacket->YawToSet = float(ui->YawToSet_Value->value());
//    m_outputpacket->PitchToSet = float(ui->PitchToSet_Value->value());
//    m_outputpacket->RollToSet = float(ui->RollToSet_Value->value());
//    m_outputpacket->DepthToSet = float(ui->DepthToSet_Value->value());
//    m_outputpacket->yaw_reg_enable = ui->YawReg_Enabler->isChecked();
//    m_outputpacket->pitch_reg_enable = ui->PitchReg_Enabler->isChecked();
//    m_outputpacket->roll_reg_enable = ui->RollReg_Enabler->isChecked();
//    m_outputpacket->depth_reg_enable = ui->DepthReg_Enabler->isChecked();
}

void MainWindow::parseInputPacket()
{
    //get data from m_inputpacket
    qDebug() << QString::number(double(m_inputpacket->yaw));
//    qDebug() << m_inputpacket->roll;

//    ui->Yaw_Value->setText(QString::number(double(m_inputpacket->yaw)));
//    ui->Pitch_Value->setText(QString::number(double(m_inputpacket->pitch)));
//    ui->Roll_Value->setText(QString::number(double(m_inputpacket->roll)));
//    ui->Depth_Value->setText(QString::number(double(m_inputpacket->depth)));


    //ui->Temperature_Value->setText(QString::number(double(m_inputpacket->temperature)));
    //ui->Core_Value->setText(QString::number(double(m_inputpacket->core)));
}

void MainWindow::func()
{
    fillOutputPacket(); //fill output packet with data
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

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    qDebug() << "tab No" << index;
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

