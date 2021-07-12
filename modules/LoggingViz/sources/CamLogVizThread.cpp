#include "CamLogVizThread.h"

CamLogVizThread::CamLogVizThread(QObject *parent) : QThread(parent){

}

void CamLogVizThread::run(){
    zmq::context_t contextSub(1);
    zmq::socket_t socketSub(contextSub, ZMQ_SUB);
    socketSub.connect(protocol::SENSING_SUB);
    socketSub.setsockopt(ZMQ_SUBSCRIBE, "CAM", 3);

    while (!stop_flag)
    { 
        sensors::Cam cam;
        zmq::message_t msgTopic = s_recv(socketSub);

        zmq::message_t msgData;
        socketSub.recv(&msgData);
        cv::Mat frame;
        cam.ParseFromArray(msgData.data(), msgData.size());

        vector<uchar> data(cam.image_data().begin(), cam.image_data().end());
        frame=cv::imdecode(data, cv::IMREAD_COLOR);

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        QImage image(frame.size().width, frame.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), frame.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
        emit sendQimage(image);

        //imshow("test", frame);
        //waitKey(30);
        
    }
    google::protobuf::ShutdownProtobufLibrary(); 
}

void CamLogVizThread::stop(){
    stop_flag = true;
}