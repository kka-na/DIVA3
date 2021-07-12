#ifndef __GLOBAL_NAME_H__
#define __GLOBAL_NAME_H__
#include "string"
#include <termios.h>

using namespace std;

namespace protocol
{
    const string SENSING_PUB = "tcp://*:5563"; //yh_GS : 10.8.0.10
    const string SENSING_SUB = "tcp://127.0.0.1:5563";
    const string SENDER_TOCLOUD_REQ_TEST = "tcp://localhost:5564"; //tcp://13.125.216.169:5555
    const string SENDER_TOCLOUD_REQ = "tcp://165.246.39.124:5564";//"54.180.155.160:22"; // ubuntu@
    const string RECEIVER_FROMMOBILE_REP_TEST = "tcp://*:5564";
} // namespace protocol

#endif// __GLOBAL_NAME_H__