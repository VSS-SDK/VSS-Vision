//
// Created by johnathan on 10/03/18.
//

#ifndef VSS_VISION_IMAGEFILEREADER_H
#define VSS_VISION_IMAGEFILEREADER_H

#include <Interfaces/IInputReader.h>
#include <opencv2/opencv.hpp>

class ImageFileReader : public IInputReader{
public:
    ImageFileReader();
    cv::Mat getFrame() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
    void initializeReceivement() override;
    void stopReceivement() override;

    void setBrightness(float) override;
    void setGain(float) override;
    void setSaturation(float) override;
    void setContrast(float) override;

    float getBrightness() override;
    float getGain() override;
    float getSaturation() override;
    float getContrast() override;

private:
    std::string source;
    cv::Mat frame;

    bool shouldCloseReader;
    bool isAValidFileSource(std::string);
};
#endif //VSS_VISION_IMAGEFILEREADER_H
