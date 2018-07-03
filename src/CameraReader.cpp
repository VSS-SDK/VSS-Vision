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
  camerasIndex.push_back(1);
}

CameraReader::~CameraReader(){
    capture.release();
}

std::vector<std::string> CameraReader::getAllPossibleSources() {
  auto camerasIndex = std::vector<std::string>();
  camerasIndex.push_back("1");
  return camerasIndex;
}

cv::Mat CameraReader::getFrame() {
    capture >> actualFrame;
    return actualFrame;
 }

void CameraReader::initializeReceivement() {
  if(!isAValidCameraIndex(actualCameraIndex)) {
    std::cerr << "[Error] Invalid camera index" << std::endl;
    return;
  }

  capture = cv::VideoCapture(1);

  capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

  capture >> actualFrame;
}

void CameraReader::setSource(std::string actualCameraIndex) {
  try {
    int cameraIndex = std::stoi(actualCameraIndex);

    if(!isAValidCameraIndex(cameraIndex)) {
      std::cerr << "[Error] Invalid camera index" << std::endl;
      return;
    }

    this->actualCameraIndex = cameraIndex;
  }
  catch(std::exception const & e)
  {
    std::cerr << "[Error] Invalid camera index" << std::endl;
  }
}

void CameraReader::pause() {
  this->runningCapture = false;
}

void CameraReader::start() {
  this->runningCapture = true;
}

void CameraReader::close() {
    this->shouldCloseReader = true;
}

void CameraReader::setBrightness(float value) {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return;
  }

  capture.set(CV_CAP_PROP_BRIGHTNESS, value/100.0);
}

void CameraReader::setGain(float value) {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return;
  }

  capture.set(CV_CAP_PROP_CONTRAST, value/100.0);
}

void CameraReader::setSaturation(float value) {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return;
  }

  capture.set(CV_CAP_PROP_SATURATION, value/100.0);
}

void CameraReader::setContrast(float value) {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return;
  }

  capture.set(CV_CAP_PROP_GAIN, value/100.0);
}

float CameraReader::getBrightness() {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return 0;
  }

  return static_cast<float>(capture.get(CV_CAP_PROP_BRIGHTNESS)*100.0);
}

float CameraReader::getGain() {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return 0;
  }

  return static_cast<float>(capture.get(CV_CAP_PROP_GAIN)*100.0);
}

float CameraReader::getSaturation() {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return 0;
  }

  return static_cast<float>(capture.get(CV_CAP_PROP_SATURATION)*100.0);
}

float CameraReader::getContrast() {
  if(!capture.isOpened()){
    std::cerr << "[Error] capture is closed" << std::endl;
    return 0;
  }

  return static_cast<float>(capture.get(CV_CAP_PROP_CONTRAST)*100.0);
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

bool CameraReader::getShouldCloseReader() {
  return shouldCloseReader;
}

bool CameraReader::getRunningCapture() {
  return runningCapture;
}

int CameraReader::getActualCameraIndex() {
  return actualCameraIndex;
}

cv::Mat CameraReader::getActualFrame() {
  return actualFrame;
}

std::vector<int> CameraReader::getCamerasIndex() {
  return camerasIndex;
}

cv::VideoCapture CameraReader::getCapture() {
  return capture;
}
