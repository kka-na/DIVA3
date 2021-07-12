#ifndef __GLOBAL_HEADER_H__
#define __GLOBAL_HEADER_H__


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cmath>
#include <sys/time.h> 
#include <cstddef>

#include <assert.h>
#include <stdlib.h>
#include <cstdlib>        // random()  RAND_MAX
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#include "unistd.h"

#include <sys/stat.h> // mkdir
#include <sys/types.h>
#include <errno.h>		//errno

#include <thread> 

#include <mutex>

//zmq
#include <zmq.hpp>


//opencv
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgcodecs.hpp>


using namespace std;
using namespace cv;

#endif //__GLOBAL_HEADER_H