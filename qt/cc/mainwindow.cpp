#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <SDL/SDL.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <QUdpSocket>
#include <QNetworkDatagram>



int baudrate = 9600;
int port = 7755;

struct InputPacket
{
    int8_t axis_X = 0;
    int8_t axis_Y = 0;
    int8_t axis_Z = 0;
    int8_t axis_W = 0;
    int8_t manipulator_rotate = 0;
    int8_t manipulator_grab = 0;
};

struct OutputPacket
{
    float yaw = 0;
    float roll = 0;
    float pitch = 0;
    float depth = 0;
};

InputPacket input;
OutputPacket output;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    timer->setInterval(60);
    timer->start();
    connect(timer, &QTimer::timeout, this, &MainWindow::func);

}


void MainWindow::set_data_to_ui()
{
    //set data
}

void MainWindow::send() {
    QByteArray data;
    data.push_back(output.yaw);
    data.push_back(output.roll);
    data.push_back(output.depth);
    data.push_back(output.pitch);

    QNetworkDatagram datagram;
    datagram.setData(data);
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, port);
//    udpSocket->write(datagram, QHostAddress("164.132.69.65"), port);
}

void MainWindow::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port);

    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingData);
}

void MainWindow::readPendingData()
{
    while (udpSocket->hasPendingDatagrams()) {
            QNetworkDatagram datagram = udpSocket->receiveDatagram();

            //do the datagram
            QByteArray data = datagram.data();
            for (int i = 0; i < data.size(); i++)
            {
                input.axis_X = data[0];
                input.axis_Y = data[1];
                input.axis_Z = data[2];
                input.axis_W = data[3];
                input.manipulator_rotate = data[4];
                input.manipulator_grab = data[5];
                set_data_to_ui();
                //хз наверное так
            }
    }
}

void MainWindow::func()
{
    SDL_Joystick* gGameController = NULL;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
    {
        qDebug() << "SDL could not initialize! SDL Error: %s\n", SDL_GetError();
    }

    //  Check for joysticks
    if( SDL_NumJoysticks() < 1 )
    {
        qDebug() << "Warning: No joysticks connected!\n";
    }
    else
    {
        //Load joystick
        gGameController = SDL_JoystickOpen(0);
        if( gGameController == NULL )
        {
            qDebug() << "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError();
        }
    }

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        qDebug() << "Error camera";
    }
    cv::Mat frame;
//    cap >> frame;
    while (1)
    {
//        qDebug() << 1;
        cap >> frame;
//        qDebug() << 2;
        cv::imshow("frame", frame);
//        qDebug() << 3;
        cv::waitKey(30);
//        qDebug() << 4;
//        char c = (char)cv::waitKey(25);
//        if (c == 27) {
//            break;
    }

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

