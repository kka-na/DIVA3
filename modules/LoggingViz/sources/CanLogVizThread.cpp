#include "CanLogVizThread.h"

CanLogVizThread::CanLogVizThread(QObject *parent) : QThread(parent){

}

void CanLogVizThread::run(){
    /*
    zmq::context_t contextSub(3);
    zmq::socket_t socketSub(contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "CAN", 3);
    */

    double velocity = 0.0;

    while (!stop_flag)
    { 
        /*
        sensors::Can can;
        zmq::message_t msgTopic = s_recv(socketSub);
        zmq::message_t msgData;
        socketSub.recv(&msgData);
        cam.ParseFromArray(msgData.data(), msgData.size());
        */

        //test
        srand(time(NULL));
        velocity = rand() % 1 + 240;
        emit sendVel(velocity);
        sleep(50);
    }
    //google::protobuf::ShutdownProtobufLibrary(); 
}

void CanLogVizThread::stop(){
    stop_flag = true;
}