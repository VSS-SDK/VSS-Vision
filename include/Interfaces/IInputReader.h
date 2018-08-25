//
// Created by johnathan on 01/03/18.
//

#ifndef VSS_VISION_ICAMERAREADER_H
#define VSS_VISION_ICAMERAREADER_H

#include <vector>
#include <cxcore.h>

class IInputReader{
public:
    virtual cv::Mat getFrame() = 0;
    virtual std::vector<std::string> getAllPossibleSources() = 0;
    virtual void setSource(std::string) = 0;
    virtual void initializeReceivement() = 0;
    virtual void stopReceivement() = 0;

    virtual void setBrightness(float) = 0;
    virtual void setGain(float) = 0;
    virtual void setSaturation(float) = 0;
    virtual void setContrast(float) = 0;

    virtual float getBrightness() = 0;
    virtual float getGain() = 0;
    virtual float getSaturation() = 0;
    virtual float getContrast() = 0;
};

#endif //VSS_VISION_ICAMERAREADER_H
