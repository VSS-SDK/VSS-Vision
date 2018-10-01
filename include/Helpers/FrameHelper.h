//
// Created by johnathan on 11/03/18.
//

#ifndef VSS_VISION_FRAMEHELPER_H
#define VSS_VISION_FRAMEHELPER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cxcore.h>
#include <Domain/Point.h>

cv::Mat changeRotation(cv::Mat, float);
cv::Mat drawRectangle(cv::Mat, std::vector<cv::Rect>);
cv::Mat drawRotatedRectangle(cv::Mat, cv::RotatedRect);
cv::Mat cropImage(cv::Mat, cv::Rect);
cv::Mat cropImage(cv::Mat, cv::Rect&, float);
cv::Mat cropImage(cv::Mat, vss::Point, vss::Point);
bool rotatedRectangleContainPoint(cv::RotatedRect, cv::Point2f);
cv::RotatedRect increaseRotatedRect(cv::RotatedRect, float, float);

#endif //VSS_VISION_FRAMEHELPER_H
