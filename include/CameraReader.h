//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_CAMERAREADER_H
#define VSS_VISION_CAMERAREADER_H

#include <vector>
#include <cxcore.h>
#include <Interfaces/ICameraReader.h>
#include <highgui.h>

class CameraReader : public ICameraReader{
public:
    CameraReader();

    void initializeCapture() override;
    std::vector<int> getAllCamerasIndex() override;
    void setCameraIndex(int) override;
    cv::Mat getActualFrame() override;
    void pause() override;
    void start() override;
    void close() override;

private:
    bool shouldCloseReader;
    bool runningCapture;
    int actualCameraIndex;
    cv::Mat actualFrame;
    std::vector<int> camerasIndex;
    cv::VideoCapture capture;

    bool isAValidCameraIndex(int);
};

#endif //VSS_VISION_CAMERAREADER_H
