#include "mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <QApplication>
#include <QDebug>
#include <SDL.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
//    return a.exec();


//    SDL_Joystick* gGameController = NULL;

//    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
//    {
//        qDebug() << "SDL could not initialize! SDL Error: %s\n", SDL_GetError();
//    }

//    //Set texture filtering to linear
//    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
//    {
//        qDebug() << "Warning: Linear texture filtering not enabled!";
//    }

//    //Check for joysticks
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

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        qDebug() << "Error camera";
    }
    cv::Mat frame;
//    cap >> frame;
    while (1)
    {
        qDebug() << 1;
        cap >> frame;
        qDebug() << 2;
        cv::imshow("frame", frame);
        qDebug() << 3;
        cv::waitKey(30);
        qDebug() << 4;
//        char c = (char)cv::waitKey(25);
//        if (c == 27) {
//            break;
//        }

    }
    cap.release();
    cv::destroyAllWindows();
    return 0;


}
