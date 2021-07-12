#ifndef CANLOGVIZTHREAD_H
#define CANLOGVIZTHREAD_H


#include "global_header.hpp"
#include "qt_header.hpp"
#include "zhelpers.hpp"
#include "protobuf/sensors.pb.h"

class CanLogVizThread : public QThread
{
    Q_OBJECT
public:
    explicit CanLogVizThread(QObject *parent = 0);
    bool stop_flag = false;
private:
    void run() override;
public slots :
    void stop();
signals:
    void sendVel(double);

};

#endif //CANLOGVIZTHREAD_H