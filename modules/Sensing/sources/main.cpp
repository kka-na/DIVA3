#include "CamSensingThread.h"

int USE_GPS = 0;
int USE_IMU = 0;
int USE_CAM = 0;
int USE_LiDAR = 0;
int USE_CAN = 0;


int main(int argc, char *argv[]){
    
    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;


    string command = "mkdir -p /home/diva2/DIVA2_DATA/"+timestamp+"_0/CAM/JPG";
    const char *c = command.c_str();
    system(c);

    mutex m;

    //(bef)
    // [Sensing Process]
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUB);
    socket.bind(protocol::SENSING_PUB);
    // socket.connect("tcp://165.246.39.124:5564");
    // socket_LiDAR.bind(protocol::SENSING_PUB); //address already in use -> 서로 다른 주소 사용해야함

    CamSensingThread camSensingThread;
    std::thread sensingthread_cam(camSensingThread.run, &socket, ref(m), timestamp);

    sensingthread_cam.join();
}