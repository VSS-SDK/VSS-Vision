/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VSS_VISION_COLORRECOGNIZER_H
#define VSS_VISION_COLORRECOGNIZER_H

#include <Domain/ColorSpace.h>
#include <Helpers/FrameHelper.h>
#include <Interfaces/IColorRecognizer.h>
#include <opencv2/imgproc/imgproc.hpp>


class ColorRecognizer : public IColorRecognizer{
public:
    void processImage(cv::Mat, int) override;
    void processImageInSector(cv::Mat, std::vector<cv::Rect>, int) override;
    void setColorRange(ColorRange) override;
    void deleteOutsidePoint(cv::RotatedRect, cv::Rect) override;

    ColorType getColor() override;
    ColorRange getColorRange() override;
    std::vector<cv::Point2f> getCenters() override;
    std::vector<cv::Rect> getRectangles() override;
    std::vector<cv::RotatedRect> getRotatedRectangles() override;
    cv::Mat getBinaryImage() override;
    cv::Mat getTestImage() override;

    void binarizesImage();
    void recognizesRectangles(unsigned int);
    void calculateCenter();
    void clear();

private:
    cv::Mat frame;
    cv::Mat binaryFrame;
    cv::Mat testImage;
    ColorRange colorRange;
    std::vector<cv::Point2f> centers;
    std::vector<cv::Rect> rectangles;
    std::vector<cv::RotatedRect> rotatedRectangles;
};
#endif // VSS_VISION_COLORRECOGNIZER_H
