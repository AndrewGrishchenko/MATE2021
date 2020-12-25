#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

#include "packets.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

//extern "C" {
//#include <SDL.h>
//}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool read();
    void send();
    void parseInputPacket();
    void fillOutputPacket();
    void read_axis();


private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_baudrate9600RadioButton_clicked();

    void on_baudrate115200RadioButton_clicked();

    void on_startCOMButton_clicked();

    void on_auto_send_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_Load_Button_clicked();

    void on_Save_Button_clicked();



    void on_YawReg_Enabler2_clicked();
    void on_PitchReg_Enabler2_clicked();
    void on_RollReg_Enabler2_clicked();
    void on_DepthReg_Enabler2_clicked();
    void on_YawReg_Enabler_clicked();
    void on_PitchReg_Enabler_clicked();
    void on_RollReg_Enabler_clicked();
    void on_DepthReg_Enabler_clicked();

    void on_Update_Button_clicked();

public slots:
    void func();
    void ready_to_read();
    void countRealSpeed();
    void test();
    void camComboBox_event(int index);
    void init_cameras();
    void processFrameAndUpdateGUI();
//    void set_data_to_ui();

private:
    cv::VideoCapture cap;
    QTimer* img_timer;
    int8_t m_real_speed = 0;
    int8_t micro_speed = 0;
    bool is_autosend = true;
    QTimer* joy_timer;
//    SDL_Joystick* joy;
    int8_t is_connected = -1;
    QTimer* timer;
    QTimer *m_timer;
    QTimer *m_speed_timer;
    Ui::MainWindow *ui;
    QUdpSocket *m_udp;
    InputPacket *m_inputpacket;
    OutputPacket *m_outputpacket;
};
#endif // MAINWINDOW_H
