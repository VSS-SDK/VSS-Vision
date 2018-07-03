//
// Created by johnathan on 10/03/18.
//

#include <ImageFileReader.h>
#include <iostream>
#include <opencv/highgui.h>
#include <zconf.h>
#include <Helpers/DefaultFilesPath.h>

ImageFileReader::ImageFileReader() {
    source = "";
}

cv::Mat ImageFileReader::getFrame() {
    return frame;
}

void ImageFileReader::initializeReceivement() {
    if(!isAValidFileSource(source)) {
        std::cerr << "[Error] Invalid file source" << std::endl;
        return;
    }

    frame = cv::imread(source);
}

std::vector<std::string> ImageFileReader::getAllPossibleSources() {
    auto sources = std::vector<std::string>();
    sources.push_back(defaultFilesPath + "/mock/images/model.jpg");
    return sources;
}

void ImageFileReader::setSource(std::string source) {
    this->source = source;
}

bool ImageFileReader::isAValidFileSource(std::string source) {
    return source == "" ? false : true;
}

void ImageFileReader::setBrightness(float) {}
void ImageFileReader::setGain(float) {}
void ImageFileReader::setSaturation(float) {}
void ImageFileReader::setContrast(float) {}

float ImageFileReader::getBrightness() { return 0; }
float ImageFileReader::getGain() { return 0; }
float ImageFileReader::getSaturation() { return 0; }
float ImageFileReader::getContrast() { return 0; }
