//
// Created by johnathan on 11/03/18.
//

#include "FrameHelper.h"

cv::Mat changeRotation(cv::Mat mat, float value) {
    try {
        cv::warpAffine(mat, mat, cv::getRotationMatrix2D(cv::Point2f(mat.cols/2, mat.rows/2), value, 1.0), mat.size());
    } catch (std::exception& e) {
        std::cout << "Exception change image rotation" << std::endl;
    }
    return mat;
}

cv::Mat changeColorSpace(cv::Mat mat, int colorSpace) {
    cv::Mat processed;
    try {
        cv::cvtColor(mat, processed, colorSpace);
    } catch (std::exception& e) {
        std::cout << "Exception change image color space" << std::endl;
    }
    return processed;
}

cv::Mat resizeImage(cv::Mat mat, cv::Point point) {
    try {
        cv::resize(mat, mat, point, 0, 0, cv::INTER_LINEAR);
    } catch (std::exception& e) {
        std::cout << "Exception resizing image" << std::endl;
    }
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

cv::Mat drawRectangle(cv::Mat mat, std::vector<cv::Rect> rectangles) {
    for (auto rect : rectangles) {
        drawRectangle(mat, rect);
    }
    return mat;
}

cv::Mat drawRectangle(cv::Mat mat, cv::Rect rect) {
    try {
        cv::rectangle(mat, rect, cv::Scalar(255, 255, 255), 1, 8, 0);
    } catch (std::exception& e) {
        std::cout << "Exception draw rect" << std::endl;
    }
    return mat;
}

cv::Mat drawRotatedRectangle(cv::Mat mat, std::vector<cv::RotatedRect> rotated) {
    for (auto rotatedRect : rotated) {
        drawRotatedRectangle(mat, rotatedRect);
    }
    return mat;
}

cv::Mat drawRotatedRectangle(cv::Mat mat, cv::RotatedRect rotated) {
    try {

    cv::Point2f vertices[4];
    rotated.points(vertices);

    for (int i = 0; i < 4; i++)
        line(mat, vertices[i], vertices[(i+1)%4], cv::Scalar(255,0,0), 1);

    } catch (std::exception& e) {
        std::cout << "Exception draw rotated rect" << std::endl;
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

cv::RotatedRect increaseRotatedRect(cv::Mat mat, cv::RotatedRect rectangle, float increase1, float increase2) {

    if (rectangle.size.width > rectangle.size.height) {
        rectangle.size.width  = int (rectangle.size.width * increase2);
        rectangle.size.height = int (rectangle.size.height * increase1);

    } else {
        rectangle.size.width  = int (rectangle.size.width * increase1);
        rectangle.size.height = int (rectangle.size.height * increase2);
    }

    return rectangle;
}

cv::Rect increaseRect(cv::Mat mat, cv::Rect rect, float increaseWidth, float increaseHeight){

    increaseWidth = rect.width * increaseWidth;
    increaseHeight = rect.height * increaseHeight;

    rect.x = rect.x - increaseWidth;
    rect.y = rect.y - increaseHeight;

    rect.width = rect.width + increaseWidth * 2;
    rect.height = rect.height + increaseHeight * 2;

    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.x + rect.width > mat.cols) rect.width = mat.cols - rect.x;
    if (rect.y + rect.height > mat.rows) rect.height = mat.rows - rect.y;

    return rect;
}
