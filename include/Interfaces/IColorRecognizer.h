//
// Created by johnathan on 08/03/18.
//

#ifndef VSS_VISION_ICOLORRECOGNIZER_H
#define VSS_VISION_ICOLORRECOGNIZER_H

#include <vector>
#include <cxcore.h>
#include <Domain/ColorRange.h>

class IColorRecognizer {
public:
    virtual void setColorRange(ColorRange) = 0;
    virtual std::vector<cv::Point> getAllColorPositions(cv::Mat) = 0;
};

#endif //VSS_VISION_ICOLORRECOGNIZER_H
