//
// Created by johnathan on 08/03/18.
//

#ifndef VSS_VISION_ICOLORRECOGNIZER_H
#define VSS_VISION_ICOLORRECOGNIZER_H

#include <vector>
#include <Domain/ColorRange.h>
#include "opencv/highgui.h"

class IColorRecognizer {
public:
    virtual void setColorRange(ColorRange) = 0;
    virtual void processImage(cv::Mat, int) = 0;
    virtual void processImageInsideSectors(cv::Mat, std::vector<cv::Rect>, int) = 0;
    virtual std::vector<cv::Rect> getRectangles() = 0;
    virtual std::vector<cv::Point2f> getCenters() = 0;
    virtual ColorType getColor() = 0;
    virtual cv::Mat getBinaryFrame() = 0;
};

#endif //VSS_VISION_ICOLORRECOGNIZER_H
