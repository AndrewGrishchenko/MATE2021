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
    void on_start_HSV_Button_clicked();
    void on_stop_HSV_Button_clicked();

    void on_Subway_ShotButton_clicked();

    void on_Subway_ClearButton_clicked();

    void on_Subway_ctrlzButton_clicked();

    void on_Map_bCircleRB_clicked();

    void on_Map_yCircleRB_clicked();

    void on_Map_rEllipseRB_clicked();

    void on_Map_gCircleRB_clicked();

    void on_Map_CtrlzButton_clicked();

    void on_Map_ClearButton_clicked();

    void on_mussels_StartButton_clicked();

    void on_mussels_StopButton_clicked();

public slots:
    void func();
    void ready_to_read();
    void countRealSpeed();
    void test();
    void camComboBox_event(int index);
    void init_cameras();
    void processFrameAndUpdateGUI();
    void hsv_setting(std::vector<int> hsv_min, std::vector<int> hsv_max);
//    void set_data_to_ui();

    void on_hue_min_slider_actionTriggered(int action);
    void on_hue_max_slider_actionTriggered(int action);
    void on_sat_min_slider_actionTriggered(int action);
    void on_sat_max_slider_actionTriggered(int action);
    void on_val_min_slider_actionTriggered(int action);
    void on_val_max_slider_actionTriggered(int action);

    void processMap();

    void closeEvent(QCloseEvent *event);

private:
    int8_t m_axis_x_old = 0;
    int8_t m_axis_y_old = 0;
    int8_t m_axis_z_old = 0;
    int8_t m_axis_w_old = 0;
    int8_t m_axis_x = 0;
    int8_t m_axis_y = 0;
    int8_t m_axis_z = 0;
    int8_t m_axis_w = 0;
    cv::VideoCapture cap;
    int camera_index = -1;
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
    std::vector<int> hsv_min = {0, 0, 0};
    std::vector<int> hsv_max = {255, 255, 255};

    //HSV
    int hue_min_label=0, hue_max_label=255, sat_min_label=0, sat_max_label=255, val_min_label=0, val_max_label=255;
    bool stop_hsv = true;
    bool dest = false;

    //SUBWAY
    int num_img;
    int imgs_widths;
    cv::Mat firstImg;
    cv::Mat secondImg;
    cv::Mat finalImg;

    //MAP
    cv::Mat map_img;
    cv::Mat old_map_img;
    cv::Mat createGrid();
    int shape_num = 1;

    //MUSSELS
    cv::Mat findCircles();
    bool stop_mussels = true;
};
#endif // MAINWINDOW_H
