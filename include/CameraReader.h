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
//#include <opencv2/videoio.hpp> // VideoCapture

class CameraReader : public IInputReader{
public:
    CameraReader();
    ~CameraReader();

    cv::Mat getFrame() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
    void initializeReceivement() override;
    void stopReceivement() override;

    bool getShouldCloseReader();
    bool getRunningCapture();
    int getActualCameraIndex();
    cv::Mat getActualFrame();
    std::vector<int> getCamerasIndex();
    cv::VideoCapture getCapture();
    bool isAValidCameraIndex(int);

    void readCameraCoefficients();
    void setMapsCalibration();
    cv::Mat getFrameWithoutDistortion(cv::Mat);

private:
    bool shouldCloseReader;
    bool runningCapture;
    int actualCameraIndex;
    cv::Mat actualFrame;
    std::vector<int> camerasIndex;
    cv::VideoCapture capture;

    cv::Mat cameraMatrix;
    cv::Mat distortionCoefficients;
    cv::Mat map1;
    cv::Mat map2;
};

#endif //VSS_VISION_CAMERAREADER_H
