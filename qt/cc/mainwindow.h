#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

#include "packets.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool read();
    void send();
    void parseInputPacket();
    void fillOutputPacket();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_baudrate9600RadioButton_clicked();

    void on_baudrate115200RadioButton_clicked();

    void on_startCOMButton_clicked();

public slots:
    void func();
    void ready_to_read();
//    void set_data_to_ui();

private:
    int8_t is_connected = -1;
    QTimer* timer;
    Ui::MainWindow *ui;
    QUdpSocket *m_udp;
    InputPacket *m_inputpacket;
    OutputPacket *m_outputpacket;
};
#endif // MAINWINDOW_H
