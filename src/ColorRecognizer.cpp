//
// Created by johnathan on 08/03/18.
//

#include <Helpers/TimeHelper.h>

#include <unistd.h>

#include <Domain/ColorRange.h>
#include <vector>
#include <cxcore.h>
#include <ColorRecognizer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <Domain/ColorSpace.h>
#include <highgui.h>

void ColorRecognizer::setColorRange(ColorRange colorRange) {
    this->colorRange = colorRange;
}

void ColorRecognizer::processImage(cv::Mat frame) {
    originalFrame = frame.clone();

    binarizesImage(originalFrame);
    rectangles = recognizesRectangles(5);
    calculateCenters();
}

void ColorRecognizer::processImageInsideSectors(cv::Mat frame, std::vector<cv::Rect> cutSquare, int increaseSquare) {

    originalFrame = frame.clone();
    
    rectangles.clear();

    for (unsigned int i = 0; i < cutSquare.size(); i++) {

        cutSquare[i].x -= int(increaseSquare / 2);
        cutSquare[i].y -= int(increaseSquare / 2);
        cutSquare[i].width  += increaseSquare;
        cutSquare[i].height += increaseSquare;

        if (cutSquare[i].x < 0) cutSquare[i].x = 0;
        if (cutSquare[i].y < 0) cutSquare[i].y = 0;
        if (cutSquare[i].x + cutSquare[i].width  > frame.cols) cutSquare[i].width  = frame.cols - cutSquare[i].x;
        if (cutSquare[i].y + cutSquare[i].height > frame.rows) cutSquare[i].height = frame.rows - cutSquare[i].y;

        cv::Mat cutFrame = cv::Mat(frame, cutSquare[i]).clone();

        binarizesImage(cutFrame);
        std::vector<cv::Rect> cuttedRectangles = recognizesRectangles(1);

        for (unsigned int j = 0; j < cuttedRectangles.size(); j++) {
            cuttedRectangles[j].x += cutSquare[i].x;
            cuttedRectangles[j].y += cutSquare[i].y;

            if (cuttedRectangles[j].x > frame.cols) cuttedRectangles[j].x = frame.cols;
            if (cuttedRectangles[j].y > frame.rows) cuttedRectangles[j].y = frame.rows;

            rectangles.push_back(cuttedRectangles[j]);
        }
    }

    calculateCenters();
}

std::vector<cv::Rect> ColorRecognizer::getRectangles() {
    return rectangles;
}

std::vector<cv::Point2f> ColorRecognizer::getCenters() {
    return centers;
}

ColorType ColorRecognizer::getColor() {
    return colorRange.colorType;
}

void ColorRecognizer::binarizesImage(cv::Mat image) {
    cv::Mat processed;
    cv::Mat processedHSV;

    cv::cvtColor(image, processedHSV, cv::COLOR_RGB2HSV_FULL);

    cv::inRange(processedHSV,
        cv::Scalar(colorRange.min[H], colorRange.min[S], colorRange.min[V]),
        cv::Scalar(colorRange.max[H], colorRange.max[S], colorRange.max[V]),
        processed);

    cv::medianBlur(processed, processed, 3);

    binaryFrame = processed.clone();
}

std::vector<cv::Rect> ColorRecognizer::recognizesRectangles(unsigned int maxNumberRect) {
    cv::Mat auxImage = binaryFrame.clone();
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(auxImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // sort in crescent order the contours vector by found area
    sort(contours.begin(), contours.end(),
        [](const std::vector<cv::Point> c1, const std::vector<cv::Point> c2){
            return cv::contourArea(c1, false) > cv::contourArea(c2, false);
        }
    );

    unsigned int numberRectFound = contours.size();

    if (numberRectFound > maxNumberRect) numberRectFound = maxNumberRect;

    std::vector<std::vector<cv::Point> > contours_poly( numberRectFound );
    std::vector<cv::Rect> boundRect( numberRectFound );

    for(unsigned int i = 0; i < numberRectFound; i++){
        approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 0, true );
        boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
        boundRect[i].x -= 1;
        boundRect[i].y -= 1;
        boundRect[i].width  += 2;
        boundRect[i].height += 2;
    }

    return boundRect;
}

void ColorRecognizer::calculateCenters() {
    auto centers = std::vector<cv::Point2f>();
    auto centimeterPoint = cv::Point2f();

    for(unsigned int i = 0 ; i < rectangles.size() ; i++){
        auto pixelPoint = getCenter(rectangles.at(i));

        centimeterPoint = {
            (float) (pixelPoint.x * vss::MAX_COORDINATE_X) / originalFrame.cols,
            (float) (pixelPoint.y * vss::MAX_COORDINATE_Y) / originalFrame.rows
        };

        centers.push_back(centimeterPoint);
    }

    this->centers = centers;
}

cv::Point2f ColorRecognizer::getCenter(cv::Rect rect) {
    cv::Point2f point = (rect.br() + rect.tl()) * 0.5;
    return point;
}

ColorRange ColorRecognizer::getColorRange() {
    return colorRange;
}

cv::Mat ColorRecognizer::getOriginalFrame() {
    return originalFrame;
}

cv::Mat ColorRecognizer::getBinaryFrame() {
    return binaryFrame;
}
