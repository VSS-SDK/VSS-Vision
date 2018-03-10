//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_CAMERAREADER_H
#define VSS_VISION_CAMERAREADER_H

#include <vector>
#include <cxcore.h>
#include <Interfaces/IImageInputReader.h>
#include <highgui.h>

class CameraReader : public IImageInputReader{
public:
    CameraReader();

    void initializeReceivement() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
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
