//
// Created by johnathan on 11/03/18.
//

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "FrameHelper.h"

void changeRotation(cv::Mat &mat, float value) {
}

void changeBrightness(cv::Mat &mat, float value) {
  cv::Mat aux;
  mat.convertTo(aux, -1, 1.0, value);
  mat = aux;
}

void changeContrast(cv::Mat &mat, float value) {
  cv::Mat aux;
  mat.convertTo(aux, -1, value, 0.0);
  mat = aux;
}

void changeSaturation(cv::Mat &mat, float value) {
  cv::Mat aux;
  mat.convertTo(aux, CV_8UC1, 1.0, value);
  mat = aux;
}

void changeExposure(cv::Mat &mat, float value) {

}

void changeGain(cv::Mat &mat, float value) {

}
