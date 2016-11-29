#include "../include/V4L2.h"

void V4L2::saveImage(std::string path){
  unsigned char* data = getArrayFromWebcam();
  writeImageToFile(data,_width,_height,path);
}

unsigned char* V4L2::getArrayFromWebcam(){
  _webcamLock.lock();
  unsigned char* data = _wrapper->frame().data;
  _webcamLock.unlock();
  return data;
}

unsigned char* V4L2::getArrayFromWebcam( unsigned char* copyTo){
  copyArray(getArrayFromWebcam(),copyTo,_size);
  return copyTo;
}

unsigned char* V4L2::getGrayscaleArrayFromWebcam(unsigned char* pixelArray){
  unsigned char* data = getArrayFromWebcam();
  float temp;
  for (long i = 0; i<_size;i+=3){
    temp = _rWeight*data[i] + _gWeight*data[i + 1]+ _bWeight*data[i + 2];
    pixelArray[i] = (unsigned char) temp;
  }
  return pixelArray;
}

V4L2::V4L2(int width, int height){
  _width = width;
  _height = height;
  _size = _width*_height*3;
  _wrapper = new V4L2Wrapper("/dev/video0", _width, _height);
}

V4L2::~V4L2(){
  delete _wrapper;
}
