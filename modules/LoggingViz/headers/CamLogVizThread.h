#ifndef CAMLOGVIZTHREAD_H
#define CAMLOGVIZTHREAD_H


#include "global_header.hpp"
#include "qt_header.hpp"
#include "zhelpers.hpp"
#include "protobuf/sensors.pb.h"

class CamLogVizThread : public QThread
{
    Q_OBJECT
public:
    explicit CamLogVizThread(QObject *parent = 0);
    bool stop_flag = false;
private:
    void run() override;
public slots :
    void stop();
signals:
    void sendQimage(QImage);

};

#endif //CAMLOGVIZTHREAD_H