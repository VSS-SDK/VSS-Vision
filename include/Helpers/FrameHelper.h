//
// Created by johnathan on 11/03/18.
//

#ifndef VSS_VISION_FRAMEHELPER_H
#define VSS_VISION_FRAMEHELPER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv/cxcore.h>
#include <Domain/Point.h>

cv::Mat getPerspectiveMatrix(cv::Mat, std::vector<vss::Point>);
cv::Mat changePerspective(cv::Mat, cv::Mat);
cv::Mat changeColorSpace(cv::Mat, int);
cv::Mat resizeImage(cv::Mat, cv::Point);

cv::Mat cropImage(cv::Mat, cv::Rect);
cv::Mat cropImage(cv::Mat, vss::Point, vss::Point);

cv::Mat drawRectangle(cv::Mat, cv::Rect);
cv::Mat drawRectangle(cv::Mat, std::vector<cv::Rect>);
cv::Mat drawRotatedRectangle(cv::Mat, cv::RotatedRect);
cv::Mat drawRotatedRectangle(cv::Mat, std::vector<cv::RotatedRect>);

bool rotatedRectangleContainPoint(cv::RotatedRect, cv::Point2f);
cv::Rect increaseRect(cv::Mat, cv::Rect, float, float);
cv::RotatedRect increaseRotatedRect(cv::Mat, cv::RotatedRect, float, float);

#endif //VSS_VISION_FRAMEHELPER_H
