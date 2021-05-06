QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0





#for control panel
INCLUDEPATH += "C:\SDL\SDL-1.2.15_32\SDL-1.2.15\include"
LIBS += -L "C:\SDL\SDL-1.2.15_32\SDL-1.2.15\lib" -lSDL

INCLUDEPATH += "C:\opencv\build\include"

LIBS += -L"C:\opencv-build\lib" \
        -llibopencv_calib3d440.dll \
        -llibopencv_core440.dll \
        -llibopencv_dnn440.dll \
        -llibopencv_features2d440.dll \
        -llibopencv_flann440.dll \
        -llibopencv_highgui440.dll \
        -llibopencv_imgcodecs440.dll \
        -llibopencv_imgproc440.dll \
        -llibopencv_ml440.dll \
        -llibopencv_objdetect440.dll \
        -llibopencv_photo440.dll \
        -llibopencv_stitching440.dll \
        -llibopencv_video440.dll \
        -llibopencv_videoio440.dll \


#for notebook
#INCLUDEPATH += "D:\Code\Qt\Tools\SDL-1.2.15_32\SDL-1.2.15\include"
#LIBS += -L "D:\Code\Qt\Tools\SDL-1.2.15_32\SDL-1.2.15\lib" -lSDL

#INCLUDEPATH += "D:\Code\opencv\build\include"
#LIBS += -L"D:\Code\opencv-build\lib" \
#        -llibopencv_calib3d440.dll \
#        -llibopencv_core440.dll \
#        -llibopencv_dnn440.dll \
#        -llibopencv_features2d440.dll \
#        -llibopencv_flann440.dll \
#        -llibopencv_highgui440.dll \
#        -llibopencv_imgcodecs440.dll \
#        -llibopencv_imgproc440.dll \
#        -llibopencv_ml440.dll \
#        -llibopencv_objdetect440.dll \
#        -llibopencv_photo440.dll \
#        -llibopencv_stitching440.dll \
#        -llibopencv_video440.dll \
#        -llibopencv_videoio440.dll \







#INCLUDEPATH += "D:\Code\Qt\Tools\SDL-1.2.15\include"
#LIBS += -L "D:\Code\Qt\Tools\SDL-1.2.15\lib\x64" -lSDL
#CXXFLAGS = -std=c++11

#INCLUDEPATH += D:\Code\opencv\build\include

#LIBS += D:\Code\opencv-build\bin\libopencv_core440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_highgui440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_imgcodecs440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_imgproc440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_features2d440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_calib3d440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_videoio440.dll

#INCLUDEPATH += "D:\Code\opencv\build\include"

#LIBS += -L"D:\Code\opencv-build\lib" \
#        -llibopencv_calib3d440.dll \
#        -llibopencv_core440.dll \
#        -llibopencv_dnn440.dll \
#        -llibopencv_features2d440.dll \
#        -llibopencv_flann440.dll \
#        -llibopencv_highgui440.dll \
#        -llibopencv_imgcodecs440.dll \
#        -llibopencv_imgproc440.dll \
#        -llibopencv_ml440.dll \
#        -llibopencv_objdetect440.dll \
#        -llibopencv_photo440.dll \
#        -llibopencv_stitching440.dll \
#        -llibopencv_video440.dll \
#        -llibopencv_videoio440.dll \

#INCLUDEPATH += "D:\\Code\\Qt\\Tools\\opencv-4.1.0\\build1\\install\\include" \
#               "D:\\Code\\Qt\\Tools\\opencv-4.1.0\\build1\\install\\include\\opencv2"

#LIBS += -L"D:\\Code\\Qt\\Tools\\opencv-4.1.0\\build1\\install\\x64\\vc16\\lib" \
#        -lopencv_calib3d410 \
#        -lopencv_core410 \
#        -lopencv_dnn410 \
#        -lopencv_features2d410 \
#        -lopencv_flann410 \
#        -lopencv_highgui410 \
#        -lopencv_imgcodecs410 \
#        -lopencv_imgproc410 \
#        -lopencv_ml410 \
#        -lopencv_objdetect410 \
#        -lopencv_photo410 \
#        -lopencv_stitching410 \
#        -lopencv_video410 \
#        -lopencv_videoio410 \

#INCLUDEPATH += D:\Code\opencv\build\include

#LIBS += D:\Code\opencv-build\bin\libopencv_core440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_highgui440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_imgcodecs440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_imgproc440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_features2d440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_calib3d440.dll
#LIBS += D:\Code\opencv-build\bin\libopencv_videoio440.dll

SOURCES += \
    customlabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    customlabel.h \
    mainwindow.h \
    packets.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
