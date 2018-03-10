//
// Created by johnathan on 10/03/18.
//

#include <ImageFileReader.h>
#include <iostream>
#include <highgui.h>
#include <zconf.h>

ImageFileReader::ImageFileReader() {
  source = "";
  runningCapture = false;
  shouldCloseReader = false;
}

void ImageFileReader::initializeReceivement() {
  if(!isAValidFileSource(source)) {
    std::cerr << "[Error] Invalid file source" << std::endl;
    return;
  }

  auto imageSource = cv::imread(source);

  while(!shouldCloseReader){
    if(runningCapture){
      actualFrame = imageSource.clone();

      signal_new_frame.emit(actualFrame);
      usleep(33333); // Simula 30 FPS
    }else{
      usleep(1000000);
    }
  }
}

std::vector<std::string> ImageFileReader::getAllPossibleSources() {
  auto sources = std::vector<std::string>();
  sources.push_back("../mock/images/model.jpg");
  return sources;
}

void ImageFileReader::setSource(std::string source) {
  this->source = source;
}

void ImageFileReader::pause() {
  this->runningCapture = false;
}

void ImageFileReader::start() {
  this->runningCapture = true;
}

void ImageFileReader::close() {
  this->shouldCloseReader = true;
}

bool ImageFileReader::isAValidFileSource(std::string source) {
  return source == "" ? false : true;
}