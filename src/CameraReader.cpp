//
// Created by johnathan on 01/03/18.
//

#include <vector>
#include <CameraReader.h>
#include <iostream>
#include <zconf.h>

CameraReader::CameraReader() {
    actualCameraIndex = -1;
    camerasIndex.push_back(1);
    hasCameraCoefficients = false;

    undistortedCoefficients();
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
    cv::Mat frame;

    do {
        capture >> frame;

        if (frame.empty())
            std::cout << "Empty image from camera" << std::endl;

    } while (frame.empty());

    if (hasCameraCoefficients)
        return undistortedFrame(frame);
    else
        return frame;
}

cv::Mat CameraReader::undistortedFrame(cv::Mat frame) {
    remap(frame, frame, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
    return frame;
}

void CameraReader::stopReceivement() {
    if (capture.isOpened()) capture.release();
}

void CameraReader::initializeReceivement() {
    if (!isAValidCameraIndex(actualCameraIndex)) {
        std::cerr << "[Error] Invalid camera index" << std::endl;
        return;
    }

    capture = cv::VideoCapture(0);

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

    std::string user(getenv("USER"));
    std::string folder = "/home/" + user + "/.vss-files/cameraCoefficients.xml";

    cv::FileStorage fs;
    fs.open(folder, cv::FileStorage::READ);

    if(fs.isOpened()){
        fs["Camera_Matrix"] >> cameraMatrix;
        fs["Distortion_Coefficients"] >> distortionCoefficients;

        hasCameraCoefficients = true;
        std::cout << "XML of Camera Coefficients founded" << std::endl;

    } else {
        std::cout << "XML of Camera Coefficients not found" << std::endl;
    }
}

void CameraReader::undistortedCoefficients() {
    readCameraCoefficients();

    if (hasCameraCoefficients)
        cv::initUndistortRectifyMap(cameraMatrix, distortionCoefficients, cv::Mat(), cameraMatrix, cv::Size(640, 480), CV_16SC2, map1, map2);
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

cv::VideoCapture CameraReader::getCapture() {
    return capture;
}