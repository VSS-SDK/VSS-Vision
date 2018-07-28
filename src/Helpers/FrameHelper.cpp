//
// Created by johnathan on 11/03/18.
//

#include "FrameHelper.h"

void changeRotation(cv::Mat &mat, float value) {
    cv::warpAffine(mat, mat, cv::getRotationMatrix2D(cv::Point2f(mat.cols/2, mat.rows/2), value, 1.0), mat.size());
}

void cropImage(cv::Mat &mat, vss::Point p1, vss::Point p2){
    cv::Rect rect = cv::Rect(cv::Point((int)p1.x, (int)p1.y),
                             cv::Point((int)p2.x, (int)p2.y));

    try{
        mat = mat(rect);
    } catch (std::exception& e){
        std::cout << "Exception cropping image" << std::endl;
    }
}

void drawRectangle(cv::Mat &mat, std::vector<cv::Rect> rectangles) {
    for (unsigned int i = 0; i < rectangles.size(); i++) {
        cv::rectangle(mat, rectangles.at(i), cv::Scalar(255, 255, 255), 2, 2, 0);
    }
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
