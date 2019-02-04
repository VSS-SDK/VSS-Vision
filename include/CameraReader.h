//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_CAMERAREADER_H
#define VSS_VISION_CAMERAREADER_H

#include <vector>
#include <opencv/cxcore.h>
#include <Interfaces/IInputReader.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <iostream>
#include <sstream>


class CameraReader : public IInputReader{
public:
    CameraReader();
    ~CameraReader();

    cv::Mat getFrame() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
    void initializeReceivement() override;
    void stopReceivement() override;

    cv::VideoCapture getCapture();
    bool isAValidCameraIndex(int);

    void undistortedCoefficients();
    cv::Mat undistortedFrame(cv::Mat);
    void readCameraCoefficients();

private:
    cv::VideoCapture capture;
    int actualCameraIndex;
    std::vector<int> camerasIndex;

    cv::Mat cameraMatrix;
    cv::Mat distortionCoefficients;
    cv::Mat map1;
    cv::Mat map2;

    bool hasCameraCoefficients;
};

#endif //VSS_VISION_CAMERAREADER_H
