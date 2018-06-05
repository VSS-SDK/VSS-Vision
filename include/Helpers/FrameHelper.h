//
// Created by johnathan on 11/03/18.
//

#ifndef VSS_VISION_FRAMEHELPER_H
#define VSS_VISION_FRAMEHELPER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cxcore.h>
#include <Domain/Point.h>

void changeRotation(cv::Mat&, float);
void cropImage(cv::Mat&, vss::Point, vss::Point);
void changeBrightness(cv::Mat&, float);
void changeContrast(cv::Mat&, float);
void changeSaturation(cv::Mat&, float);
void changeExposure(cv::Mat&, float);
void changeGain(cv::Mat&, float);

#endif //VSS_VISION_FRAMEHELPER_H
