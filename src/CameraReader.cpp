//
// Created by johnathan on 01/03/18.
//

#include <vector>
#include <CameraReader.h>
#include <iostream>
#include <zconf.h>

CameraReader::CameraReader() {
  initialized = false;
  runningCapture = false;
  shouldCloseReader = false;
  actualCameraIndex = -1;
}


std::vector<int> CameraReader::getAllCamerasIndex() {
  return std::vector<int>();
}

void CameraReader::initializeCapture() {
  if(!initialized){
    std::cerr << "[Error] Capture not initialized" << std::endl;
    return;
  }

  if(!isAValidCameraIndex(actualCameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  while(!shouldCloseReader){
    if(runningCapture){
      // Faz um monte de coisa
      usleep(1000000);
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
  return cv::Mat();
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
