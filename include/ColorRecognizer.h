//
// Created by johnathan on 08/03/18.
//

#ifndef VSS_VISION_COLORRECOGNIZER_H
#define VSS_VISION_COLORRECOGNIZER_H

#include <Interfaces/IColorRecognizer.h>

class ColorRecognizer : public IColorRecognizer{
public:
    void setColorRange(ColorRange) override;
    std::vector<cv::Point> getAllColorPositions(cv::Mat) override;

private:
    ColorRange colorRange;
};
#endif //VSS_VISION_COLORRECOGNIZER_H
