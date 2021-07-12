#include "global_header.hpp"
#include "protobuf/sensors.pb.h"
#include "zhelpers.hpp"

#pragma warning(disable : 4996) //error C4996 뜨는 경우

class CamSensingThread
{

public:
    CamSensingThread();
    static void run(zmq::socket_t *publisher, mutex &m, string dir); 
};