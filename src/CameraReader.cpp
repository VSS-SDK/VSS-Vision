//
// Created by johnathan on 01/03/18.
//

#include <vector>
#include <CameraReader.h>
#include <iostream>
#include <zconf.h>

CameraReader::CameraReader() {
  runningCapture = false;
  shouldCloseReader = false;
  actualCameraIndex = -1;

  // Simulando uma camera
  camerasIndex.push_back(0);

}

std::vector<int> CameraReader::getAllCamerasIndex() {
  return std::vector<int>();
}

void CameraReader::initializeCapture() {
  if(!isAValidCameraIndex(actualCameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  capture = cv::VideoCapture(0);

  while(!shouldCloseReader){
    if(runningCapture){
      capture >> actualFrame;
      
      signal_new_frame.emit(actualFrame);
      
    }else{
      usleep(1000000);
    }
  }
}

void CameraReader::setCameraIndex(int actualCameraIndex) {
  if(!isAValidCameraIndex(actualCameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  this->actualCameraIndex = actualCameraIndex;
}

cv::Mat CameraReader::getActualFrame() {
  return actualFrame.clone();
}

void CameraReader::pause() {
  this->runningCapture = false;
}

void CameraReader::start() {
  this->runningCapture = true;
}

bool CameraReader::isAValidCameraIndex(int cameraIndex) {
  if(cameraIndex < 0)
    return false;

  for(unsigned int i = 0 ; i < camerasIndex.size() ; i++){
    if(cameraIndex == camerasIndex.at(i))
      return true;
  }

  return false;
}

void CameraReader::close() {
  this->shouldCloseReader = true;
}