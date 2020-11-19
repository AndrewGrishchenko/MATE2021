#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_baudrate9600RadioButton_clicked();

    void on_baudrate115200RadioButton_clicked();

    void on_startCOMButton_clicked();

public slots:
    void func();
    void initSocket();
    void readPendingData();
    void set_data_to_ui();
    void send();

private:
    QTimer* timer;
    Ui::MainWindow *ui;
    QUdpSocket* udpSocket;
};
#endif // MAINWINDOW_H
