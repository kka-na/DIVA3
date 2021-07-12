#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global_header.hpp"
#include "qt_header.hpp"
#include "Timestamp.h"


#include "informdialog.h"
#include "CamLogVizThread.h"
#include "CanLogVizThread.h"

#include "SpeedoMeter.h"

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: 
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void makeCAMEnvironment();
    void makeGPSEnvironment();
    void makeCANEnvironment();

public: 
    //for protobuf
    mutex m;
    //for gps
    QWebEngineView *gpsMapView;
    QWebEnginePage *gpsMapPage;
    int gpscnt;
    QString gpsaddr;
    //for camera
    QLabel *camWidget;
    //for can
    class SpeedoMeter::SpeedoMeter *canSpeedWidget;
    

private:
	Ui::MainWindow *ui;
    Timestamp ts;
	class CamLogVizThread::CamLogVizThread *cmlvt;
    class CanLogVizThread::CanLogVizThread *cnlvt;

public slots:
    void displayGPS(QString latitude, QString longtitude, double hdop);
	void displayCam(QImage image);
    void displayVel(double value);

private slots :
	void initializeClass();
    void aboutDIVA();
    void setUsage();

}
;
#endif //MAINWINDOW_H
