//
// Created by johnathan on 08/03/18.
//

#ifndef VSS_VISION_COLORRECOGNIZER_H
#define VSS_VISION_COLORRECOGNIZER_H

#include <Interfaces/IColorRecognizer.h>

class ColorRecognizer : public IColorRecognizer{
public:
    void setColorRange(ColorRange) override;
    void processImage(cv::Mat) override;
    void processImageInsideSectors(cv::Mat, std::vector<cv::Point>, int) override;
    std::vector<cv::Rect> getRectangles() override;
    std::vector<cv::Point> getCenters() override;

    void binarizesImage();
    void recognizesRectangles();
    void calculateCenters();
    cv::Point getCenter(cv::Rect);
    ColorRange getColorRange();
    cv::Mat getOriginalFrame();
    cv::Mat getBinaryFrame();

private:
    ColorRange colorRange;
    cv::Mat originalFrame;
    cv::Mat binaryFrame;
    std::vector<cv::Rect> rectangles;
    std::vector<cv::Point> centers;
};
#endif //VSS_VISION_COLORRECOGNIZER_H
