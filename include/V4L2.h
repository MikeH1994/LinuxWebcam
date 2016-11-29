#ifndef H_V4L2_H
#define H_V4L2_H

#include "V4L2Wrapper.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <thread>

class V4L2:public Utils{
private:
  int _width;
  int _height;
  long _size;
  unsigned char* _transferArray;
  V4L2Wrapper* _wrapper;
  std::recursive_mutex _webcamLock;
public:
  V4L2(int width, int height);
  ~V4L2();
  void saveImage(std::string path);
  unsigned char* getArrayFromWebcam(unsigned char* copyTo);
  unsigned char* getGrayscaleArrayFromWebcam(unsigned char* pixelArray);
  unsigned char* getArrayFromWebcam();
};
#endif
