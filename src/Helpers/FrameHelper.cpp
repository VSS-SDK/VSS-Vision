//
// Created by johnathan on 11/03/18.
//

#include "FrameHelper.h"

cv::Mat changeRotation(cv::Mat mat, float value) {
    cv::warpAffine(mat, mat, cv::getRotationMatrix2D(cv::Point2f(mat.cols/2, mat.rows/2), value, 1.0), mat.size());
    return mat;
}

cv::Mat cropImage(cv::Mat mat, cv::Rect rect) {
    try{
        mat = mat(rect);
    } catch (std::exception& e){
        std::cout << "Exception cropping image" << std::endl;
    }
    return mat;
}

cv::Mat cropImage(cv::Mat mat, vss::Point p1, vss::Point p2) {
    cv::Rect rect = cv::Rect(cv::Point((int)p1.x, (int)p1.y),
                             cv::Point((int)p2.x, (int)p2.y));

    return cropImage(mat, rect);
}

cv::Mat cropImage(cv::Mat mat, cv::Rect rect, float increase){
    rect.x = rect.x - int( float(rect.width) * increase );
    rect.y = rect.y - int( float(rect.height) * increase );
    rect.width = rect.width + int( float(rect.width) * increase ) * 2;
    rect.height = rect.height + int( float(rect.height) * increase ) * 2;

    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.width > mat.cols) rect.x = mat.cols;
    if (rect.height > mat.rows) rect.y = mat.rows;

    return cropImage(mat, rect);
}

cv::Mat drawRectangle(cv::Mat mat, std::vector<cv::Rect> rectangles) {
    for (unsigned int i = 0; i < rectangles.size(); i++) {
        cv::rectangle(mat, rectangles.at(i), cv::Scalar(255, 255, 255), 2, 2, 0);
    }
    return mat;
}

bool rotatedRectangleContainPoint(cv::RotatedRect rectangle, cv::Point2f point) {

    cv::Point2f corners[4];
    rectangle.points(corners);

    cv::Point2f *lastItemPointer = (corners + sizeof corners / sizeof corners[0]);
    std::vector<cv::Point2f> contour(corners, lastItemPointer);

    double indicator = pointPolygonTest(contour, point, false);

    return indicator >= 0;
}