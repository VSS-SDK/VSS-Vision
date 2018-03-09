//
// Created by johnathan on 08/03/18.
//

#ifndef VSS_VISION_ICOLORRECOGNIZEROPTIMIZED_H
#define VSS_VISION_ICOLORRECOGNIZEROPTIMIZED_H

#include "IColorRecognizer.h"

class IColorRecognizerOptimized : public IColorRecognizer{
public:
    virtual void setColorRange(ColorRange) = 0;
    virtual std::vector<cv::Point> getAllColorPositions(cv::Mat) = 0;
    virtual std::vector<cv::Point> getAllColorPositionsInsideSections(cv::Mat, std::vector<cv::Point>, int) = 0;
};
#endif //VSS_VISION_ICOLORRECOGNIZEROPTIMIZED_H
