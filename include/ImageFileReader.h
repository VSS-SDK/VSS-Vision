//
// Created by johnathan on 10/03/18.
//

#ifndef VSS_VISION_IMAGEFILEREADER_H
#define VSS_VISION_IMAGEFILEREADER_H

#include <Interfaces/IImageInputReader.h>
//#include <opencv2/imgcodecs.hpp> //imread

class ImageFileReader : public IImageInputReader{
public:
    ImageFileReader();
    void initializeReceivement() override;
    std::vector<std::string> getAllPossibleSources() override;
    void setSource(std::string) override;
    void pause() override;
    void start() override;
    void close() override;

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
    bool runningCapture;
    bool shouldCloseReader;
    cv::Mat actualFrame;

    bool isAValidFileSource(std::string);
};
#endif //VSS_VISION_IMAGEFILEREADER_H
