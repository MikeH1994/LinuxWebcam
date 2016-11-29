#ifndef H_CAMERA_H
#define H_CAMERA_H

#include"CImg.h"
#include"Filter.h"
#include "V4L2.h"

#include <chrono>
#include <thread>
#include <algorithm>
#include <unistd.h>

class Camera:public Utils{
protected:
  bool _applyFilter = false;
  bool _update = true;
  unsigned char* _pixelValue;
  int _width = 640;
  int _height = 480;
  long _size = _width*_height*3;
  V4L2* _webcam;
  Filter* _filter;
  std::recursive_mutex _pixelLock;
  std::thread _updateThread;
  cimg_library::CImg<unsigned char> *_image;
  cimg_library::CImgDisplay *_imageDisplay;
  
  void update();
  void nextFrame();
  void initialise();
  void filter();
  void updateImageDisplay();
public:
	void run();
	Camera();
  ~Camera();
};
#endif
