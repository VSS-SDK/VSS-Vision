//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_CAMERAREADER_H
#define VSS_VISION_CAMERAREADER_H

#include <vector>
#include <cxcore.h>
#include <Interfaces/IInputReader.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/videoio.hpp> // VideoCapture

class CameraReader : public IInputReader{
public:
    CameraReader();

    void initializeReceivement() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
    void pause() override;
    void start() override;
    void close() override;
    cv::Mat getFrame() override;

    void setBrightness(float) override;
    void setGain(float) override;
    void setSaturation(float) override;
    void setContrast(float) override;

    float getBrightness() override;
    float getGain() override;
    float getSaturation() override;
    float getContrast() override;

    bool getShouldCloseReader();
    bool getRunningCapture();
    int getActualCameraIndex();
    cv::Mat getActualFrame();
    std::vector<int> getCamerasIndex();
    cv::VideoCapture getCapture();
    bool isAValidCameraIndex(int);

private:
    bool shouldCloseReader;
    bool runningCapture;
    int actualCameraIndex;
    cv::Mat actualFrame;
    std::vector<int> camerasIndex;
    cv::VideoCapture capture;
};

#endif //VSS_VISION_CAMERAREADER_H
