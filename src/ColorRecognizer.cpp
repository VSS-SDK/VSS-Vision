//
// Created by johnathan on 08/03/18.
//

#include <Domain/ColorRange.h>
#include <vector>
#include <cxcore.h>
#include <ColorRecognizer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <Domain/ColorSpace.h>

void ColorRecognizer::setColorRange(ColorRange colorRange) {
  this->colorRange = colorRange;
}

void ColorRecognizer::processImage(cv::Mat frame) {
  originalFrame = frame.clone();

  binarizesImage();
  recognizesRectangles();
  calculateCenters();
}

void ColorRecognizer::binarizesImage() {
  cv::Mat processed;

  cv::inRange(originalFrame,
              cv::Scalar(colorRange.min[H], colorRange.min[S], colorRange.min[V]),
              cv::Scalar(colorRange.max[H], colorRange.max[H], colorRange.max[V]),
              processed);

  cv::medianBlur(processed, processed, 3);

  binaryFrame = processed.clone();
}

void ColorRecognizer::recognizesRectangles() {
  cv::Mat auxImage = binaryFrame.clone();
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(auxImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

  std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
  std::vector<cv::Rect> boundRect( contours.size() );

  for(unsigned int i = 0; i < contours.size(); i++){
    approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 0, true );
    boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
  }

  rectangles = boundRect;
}

void ColorRecognizer::calculateCenters() {
  auto centers = std::vector<cv::Point>();

  for(unsigned int i = 0 ; i < rectangles.size() ; i++){
    centers.push_back(getCenter(rectangles.at(i)));
  }

  this->centers = centers;
}

cv::Mat ColorRecognizer::getBinaryImage() {
  return binaryFrame;
}

void ColorRecognizer::processImageInsideSectors(cv::Mat, std::vector<cv::Point>, int) {

}

cv::Point ColorRecognizer::getCenter(cv::Rect rect) {
  cv::Point point = (rect.br() + rect.tl())*0.5;
  return point;
}

std::vector<cv::Rect> ColorRecognizer::getRectangles() {
  return rectangles;
}

std::vector<cv::Point> ColorRecognizer::getCenters() {
  return centers;
}


