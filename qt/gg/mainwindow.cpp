#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

int baudrate = 9600;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
