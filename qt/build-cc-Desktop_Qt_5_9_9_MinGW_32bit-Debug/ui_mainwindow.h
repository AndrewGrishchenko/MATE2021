/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *verticalWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QComboBox *camComboBox1;
    QFrame *frame1;
    QWidget *tab2;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QComboBox *camComboBox2;
    QHBoxLayout *horizontalLayout;
    QFrame *frame2;
    QWidget *verticalWidget_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *baudrate9600RadioButton;
    QRadioButton *baudrate115200RadioButton;
    QLabel *COMPortText;
    QLineEdit *COMPortLineEdit;
    QPushButton *startCOMButton;
    QSpacerItem *verticalSpacer;
    QLabel *DataText;
    QSpacerItem *horizontalSpacer;
    QLabel *dirData;
    QLabel *powData;
    QLabel *brightnessData;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setBaseSize(QSize(0, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(verticalWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(verticalWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout_3 = new QGridLayout(tab1);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        camComboBox1 = new QComboBox(tab1);
        camComboBox1->setObjectName(QStringLiteral("camComboBox1"));

        verticalLayout->addWidget(camComboBox1);

        frame1 = new QFrame(tab1);
        frame1->setObjectName(QStringLiteral("frame1"));
        frame1->setFrameShape(QFrame::StyledPanel);
        frame1->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame1);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        gridLayout_4 = new QGridLayout(tab2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        camComboBox2 = new QComboBox(tab2);
        camComboBox2->setObjectName(QStringLiteral("camComboBox2"));

        verticalLayout_2->addWidget(camComboBox2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame2 = new QFrame(tab2);
        frame2->setObjectName(QStringLiteral("frame2"));
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame2);

        verticalWidget_3 = new QWidget(tab2);
        verticalWidget_3->setObjectName(QStringLiteral("verticalWidget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalWidget_3->sizePolicy().hasHeightForWidth());
        verticalWidget_3->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(verticalWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        baudrate9600RadioButton = new QRadioButton(verticalWidget_3);
        baudrate9600RadioButton->setObjectName(QStringLiteral("baudrate9600RadioButton"));
        baudrate9600RadioButton->setChecked(true);

        verticalLayout_3->addWidget(baudrate9600RadioButton);

        baudrate115200RadioButton = new QRadioButton(verticalWidget_3);
        baudrate115200RadioButton->setObjectName(QStringLiteral("baudrate115200RadioButton"));

        verticalLayout_3->addWidget(baudrate115200RadioButton);

        COMPortText = new QLabel(verticalWidget_3);
        COMPortText->setObjectName(QStringLiteral("COMPortText"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(COMPortText->sizePolicy().hasHeightForWidth());
        COMPortText->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(COMPortText);

        COMPortLineEdit = new QLineEdit(verticalWidget_3);
        COMPortLineEdit->setObjectName(QStringLiteral("COMPortLineEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(COMPortLineEdit->sizePolicy().hasHeightForWidth());
        COMPortLineEdit->setSizePolicy(sizePolicy4);

        verticalLayout_3->addWidget(COMPortLineEdit);

        startCOMButton = new QPushButton(verticalWidget_3);
        startCOMButton->setObjectName(QStringLiteral("startCOMButton"));

        verticalLayout_3->addWidget(startCOMButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer);

        DataText = new QLabel(verticalWidget_3);
        DataText->setObjectName(QStringLiteral("DataText"));

        verticalLayout_3->addWidget(DataText);

        horizontalSpacer = new QSpacerItem(190, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        dirData = new QLabel(verticalWidget_3);
        dirData->setObjectName(QStringLiteral("dirData"));

        verticalLayout_3->addWidget(dirData);

        powData = new QLabel(verticalWidget_3);
        powData->setObjectName(QStringLiteral("powData"));

        verticalLayout_3->addWidget(powData);

        brightnessData = new QLabel(verticalWidget_3);
        brightnessData->setObjectName(QStringLiteral("brightnessData"));

        verticalLayout_3->addWidget(brightnessData);


        horizontalLayout->addWidget(verticalWidget_3);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout->addWidget(verticalWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 960, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Main", Q_NULLPTR));
        baudrate9600RadioButton->setText(QApplication::translate("MainWindow", "9600 BaudRate", Q_NULLPTR));
        baudrate115200RadioButton->setText(QApplication::translate("MainWindow", "115200 BaudRate", Q_NULLPTR));
        COMPortText->setText(QApplication::translate("MainWindow", "COMPort:", Q_NULLPTR));
        startCOMButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        DataText->setText(QApplication::translate("MainWindow", "Data:", Q_NULLPTR));
        dirData->setText(QApplication::translate("MainWindow", "Direction: -1", Q_NULLPTR));
        powData->setText(QApplication::translate("MainWindow", "MotorPower: -1", Q_NULLPTR));
        brightnessData->setText(QApplication::translate("MainWindow", "LightBrightness: -1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "microROV", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
