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
    virtual void processImage(cv::Mat) = 0;
    virtual void setColorRange(ColorRange) = 0;
    virtual void deleteOutsidePoint(cv::RotatedRect) = 0;

    virtual ColorType getColor() = 0;
    virtual ColorRange getColorRange() = 0;
    virtual std::vector<cv::Point2f> getCenters() = 0;
    virtual std::vector<cv::Rect> getRectangles() = 0;
    virtual std::vector<cv::RotatedRect> getRotatedRectangles() = 0;
    virtual cv::Mat getBinaryImage() = 0;

};

#endif // VSS_VISION_ICOLORRECOGNIZER_H
