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

cv::Mat cropImage(cv::Mat mat, cv::Rect &rect, float increase){
    rect.x = int (rect.x - rect.width * increase );
    rect.y = int (rect.y - rect.height * increase );
    rect.width = int (rect.width + (rect.width * increase ) * 2);
    rect.height = int (rect.height + (rect.height * increase ) * 2);

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

cv::Mat drawRotatedRectangle(cv::Mat mat, cv::RotatedRect rotated) {
    cv::Point2f vertices[4];
    rotated.points(vertices);

    for (int i = 0; i < 4; i++)
        line(mat, vertices[i], vertices[(i+1)%4], cv::Scalar(255,255,255), 1);

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

cv::RotatedRect increaseRotatedRect(cv::RotatedRect rectangle, float increase1, float increase2) {

    if (rectangle.size.width > rectangle.size.height) {
        rectangle.size.width  = int (rectangle.size.width * increase2);
        rectangle.size.height = int (rectangle.size.height * increase1);

    } else {
        rectangle.size.width  = int (rectangle.size.width * increase1);
        rectangle.size.height = int (rectangle.size.height * increase2);
    }

    return rectangle;
}
