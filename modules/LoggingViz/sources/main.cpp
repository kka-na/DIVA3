#include "mainwindow.h"
#include "CamLogVizThread.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    // CAM
    //thread camLogVizThread(&CamLogVizThread::run, &mCamLogViz, &contextSub);
    //camLogVizThread.join();

    return a.exec();

}