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
    //setMapsCalibration();

    // Simulando uma camera
    camerasIndex.push_back(1);
}

CameraReader::~CameraReader() {
    capture.release();
}

std::vector<std::string> CameraReader::getAllPossibleSources() {
    auto camerasIndex = std::vector<std::string>();
    camerasIndex.push_back("1");
    return camerasIndex;
}

cv::Mat CameraReader::getFrame() {
    cv::Mat newFrame;
    capture >> newFrame;

   // if (!newFrame.empty()) {
        actualFrame = newFrame;
   // }

    //return getFrameWithoutDistortion(actualFrame);
    return (actualFrame);
}

void CameraReader::stopReceivement() {
    if (capture.isOpened()) capture.release();
}

void CameraReader::initializeReceivement() {
    if (!isAValidCameraIndex(actualCameraIndex)) {
        std::cerr << "[Error] Invalid camera index" << std::endl;
        return;
    }

    capture = cv::VideoCapture(1);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    if (!capture.isOpened()) {
        std::cerr << "[Error] Camera cannot open" << std::endl;
    }

}

void CameraReader::setSource(std::string actualCameraIndex) {
    try {
        int cameraIndex = std::stoi(actualCameraIndex);

        if (!isAValidCameraIndex(cameraIndex)) {
            std::cerr << "[Error] Invalid camera index" << std::endl;
            return;
        }

        this->actualCameraIndex = cameraIndex;
    }
    catch (std::exception const &e) {
        std::cerr << "[Error] Invalid camera index" << std::endl;
    }
}

void CameraReader::readCameraCoefficients() {
    cv::FileStorage fs;
    fs.open("cameraCoefficients.xml", cv::FileStorage::READ);
    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> distortionCoefficients;
}

void CameraReader::setMapsCalibration() {
    readCameraCoefficients();
    cv::initUndistortRectifyMap(cameraMatrix, distortionCoefficients,
                                cv::Mat(), cameraMatrix, cv::Size(1280, 720),
                                CV_16SC2, map1, map2);
}

cv::Mat CameraReader::getFrameWithoutDistortion(cv::Mat frame) {
    cv::Mat frameWithoutDistortion;
    remap(frame, frameWithoutDistortion, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
    return frameWithoutDistortion;
}

bool CameraReader::isAValidCameraIndex(int cameraIndex) {
    if (cameraIndex < 0)
        return false;

    for (unsigned int i = 0; i < camerasIndex.size(); i++) {
        if (cameraIndex == camerasIndex.at(i))
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