#include "CamSensingThread.h"

#define MILL 1000000

CamSensingThread::CamSensingThread(){

}

void CamSensingThread::run(zmq::socket_t *pubSock, mutex &m, string dir){
	

    VideoCapture *cap = new VideoCapture(CAP_DSHOW);
    int open = cap->open(0);
    /*
    cap->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap->set(cv::CAP_PROP_FRAME_WIDTH, 1080);
    cap->set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    cap->set(cv::CAP_PROP_FPS, 15);
	*/
    while (open){
		sensors::Cam cam;
		Mat frame;
		cap->read(frame);
		resize(frame, frame, Size(640, 360),0,0,cv::INTER_LINEAR);
		/*
		imshow("Web Cam Capture", frame);
		char ch = waitKey(30);
		if(ch == 27) break;*/
		if (!frame.empty()){
			struct timeval tv;
			gettimeofday(&tv, NULL);
			cam.set_timestamp((tv.tv_sec * MILL) + (tv.tv_usec));
			cam.set_cols(frame.cols);
			cam.set_rows(frame.rows);

			vector<uchar> buffer;
			imencode(".jpg", frame, buffer);
			size_t totalsize = buffer.size();
			cam.mutable_image_data()->resize(totalsize);
			memcpy((void *)cam.mutable_image_data()->data(), (void *)buffer.data(), totalsize);

			int data_len = cam.ByteSize();
			unsigned char data[data_len] = "\0";
			cam.SerializeToArray(data, data_len);

			zmq::message_t zmqData(data_len);
			memcpy((void *)zmqData.data(), data, data_len);
			m.lock();
			s_send_idx(*pubSock, SENSOR_CAM);
			s_send(*pubSock, zmqData);
			m.unlock();
		} 
	} 

}
