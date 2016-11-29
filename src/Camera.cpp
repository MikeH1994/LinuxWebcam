#include"../include/Camera.h"

Camera::~Camera(){
  delete _webcam;
  delete _filter;
	delete _image;
	delete _imageDisplay;
}
Camera::Camera(){
  _webcam = new V4L2(_width,_height);
  _filter = new Filter(_width,_height);
  _image = new cimg_library::CImg<unsigned char>(_width,_height,1,3,0);
  _imageDisplay = new cimg_library::CImgDisplay(*_image,"Cam_001");
  _imageDisplay->show();
}


void Camera::updateImageDisplay(){
	//updates the CImg windows displaying camera output
	int x;
	int y;
	
	for(long i = 0; i<_width*_height; i+=1){
		x = i%_width;
		y = i/_width;
		(*_image)(x,y,0,0) = _pixelValue[i*3];
		(*_image)(x,y,0,1) = _pixelValue[i*3 +1];
		(*_image)(x,y,0,2) = _pixelValue[i*3 + 2];
	}
	_image->display(*_imageDisplay);
}

void Camera::run(){
  _updateThread = std::thread(&Camera::update,this);
  _updateThread.detach();
  
  while(!_imageDisplay->is_closed()){
		std::this_thread::sleep_for(std::chrono::milliseconds( 100 ) );
	}
	_update = false;
	_pixelLock.lock();
  return;
}

void Camera::update(){
  while(_update){
    nextFrame();
  }
}

void Camera::nextFrame(){
  /*
  update the _pixelValue array with new values from webcam
  */
  _pixelLock.lock();
  _pixelValue = _webcam->getArrayFromWebcam();
  if (_applyFilter){
  	filter();
  }
  updateImageDisplay();
  _pixelLock.unlock();
}

void Camera::filter(){
	_filter->runMedianFilter(_pixelValue);
}
