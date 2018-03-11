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

std::vector<std::string> CameraReader::getAllPossibleSources() {
  auto camerasIndex = std::vector<std::string>();
  camerasIndex.push_back("0");
  return camerasIndex;
}

void CameraReader::initializeReceivement() {
  if(!isAValidCameraIndex(actualCameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  capture = cv::VideoCapture(0);
  signal_loaded_capture.emit(true);

  while(!shouldCloseReader){
    if(runningCapture){
      capture >> actualFrame;
      
      signal_new_frame.emit(actualFrame);
      
    }else{
      usleep(1000000);
    }
  }
}

void CameraReader::setSource(std::string actualCameraIndex) {
  int cameraIndex = std::stoi(actualCameraIndex);

  if(!isAValidCameraIndex(cameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  this->actualCameraIndex = cameraIndex;
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

void CameraReader::setBrightness(float value) {
  capture.set(CV_CAP_PROP_BRIGHTNESS, value/100.0);
}

void CameraReader::setGain(float value) {
  capture.set(CV_CAP_PROP_CONTRAST, value/100.0);
}

void CameraReader::setSaturation(float value) {
  capture.set(CV_CAP_PROP_SATURATION, value/100.0);
}

void CameraReader::setContrast(float value) {
  capture.set(CV_CAP_PROP_GAIN, value/100.0);
}

float CameraReader::getBrightness() {
  return static_cast<float>(capture.get(CV_CAP_PROP_BRIGHTNESS)*100.0);
}

float CameraReader::getGain() {
  return static_cast<float>(capture.get(CV_CAP_PROP_GAIN)*100.0);
}

float CameraReader::getSaturation() {
  return static_cast<float>(capture.get(CV_CAP_PROP_SATURATION)*100.0);
}

float CameraReader::getContrast() {
  return static_cast<float>(capture.get(CV_CAP_PROP_CONTRAST)*100.0);
}
