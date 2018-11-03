/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <ColorRecognizer.h>

void ColorRecognizer::processImage(cv::Mat image, int maxRecognizesRectangles) {
    frame = image.clone();

    clear();

    binarizesImage();
    recognizesRectangles(maxRecognizesRectangles);
    calculateCenter();
}

void ColorRecognizer::processImageInSector(cv::Mat image, std::vector<cv::Rect> rect, int maxRecognizesRectangles) {
    clear();
    unsigned long changeCoordinateInVector = 0;
    
    
    for (unsigned int i = 0; i < rect.size(); i++) {
        rect[i] = increaseRect(image, rect[i], 0.5 ,0.5);
        frame = cropImage(image, rect[i]);

        binarizesImage();
        recognizesRectangles(maxRecognizesRectangles);

        for (unsigned long j = changeCoordinateInVector; j < rectangles.size(); j++) {
            rectangles[j].x += rect[i].x;
            rectangles[j].y += rect[i].y;
            rotatedRectangles[j].center.x += rect[i].x;
            rotatedRectangles[j].center.y += rect[i].y;

            std::cout << "Teste: " << rectangles[j] << std::endl;
        }

        changeCoordinateInVector = rectangles.size();
    }
    
    calculateCenter();
}

void ColorRecognizer::binarizesImage() {
    cv::Mat processed;
    cv::Mat processedHSV;

    cv::cvtColor(frame, processedHSV, cv::COLOR_RGB2HSV_FULL);

    cv::inRange(processedHSV,
        cv::Scalar(colorRange.min[H], colorRange.min[S], colorRange.min[V]),
        cv::Scalar(colorRange.max[H], colorRange.max[S], colorRange.max[V]),
        processed);

    cv::medianBlur(processed, processed, 5);

    binaryFrame = processed.clone();
}

void ColorRecognizer::recognizesRectangles(unsigned int maxRecognizesRectangles) {
    std::vector< cv::Vec4i > hierarchy;
    std::vector< std::vector<cv::Point> > contours;

    cv::findContours(binaryFrame.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // sort in crescent order the contours vector by found area
    sort(contours.begin(), contours.end(),
        [](const std::vector<cv::Point> c1, const std::vector<cv::Point> c2){
            return cv::contourArea(c1, false) > cv::contourArea(c2, false);
        }
    );

    if (contours.size() < maxRecognizesRectangles)
        maxRecognizesRectangles = contours.size();

    std::vector<cv::Rect> vectorRect( maxRecognizesRectangles );
    std::vector<cv::RotatedRect> vectorRotatedRect( maxRecognizesRectangles );
    std::vector<std::vector<cv::Point>> contours_poly( maxRecognizesRectangles );

    for(unsigned int i = 0; i < maxRecognizesRectangles; i++){
        vectorRotatedRect[i] = cv::minAreaRect( cv::Mat(contours[i]) );
        approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 0, true );
        vectorRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
//        vectorRect[i].x -= 1;
//        vectorRect[i].y -= 1;
//        vectorRect[i].width  += 2;
//        vectorRect[i].height += 2;
    }

    for(unsigned int i = 0; i < maxRecognizesRectangles; i++) {
        rectangles.push_back(vectorRect[i]);
        rotatedRectangles.push_back(vectorRotatedRect[i]);
    }
}

void ColorRecognizer::calculateCenter(){
    for (auto r : rotatedRectangles) {
        centers.push_back(r.center);
    }
}

void ColorRecognizer::deleteOutsidePoint(cv::RotatedRect rotated, cv::Rect rect) {

    // change rotated rect global coordinate to local coordinate
    rotated.center.x = abs(rotated.center.x - rect.x);
    rotated.center.y = abs(rotated.center.y - rect.y);

    std::vector<cv::Point2f> auxCenters;
    std::vector<cv::Rect> auxRectangles;
    std::vector<cv::RotatedRect> auxRotatedRectangles;

    for (unsigned int i = 0; i < rotatedRectangles.size(); i++) {
        if (rotatedRectangleContainPoint( rotated, rotatedRectangles[i].center )) {
            auxCenters.push_back(centers[i]);
            auxRectangles.push_back(rectangles[i]);
            auxRotatedRectangles.push_back(rotatedRectangles[i]);
        }
    }

    centers = auxCenters;
    rectangles = auxRectangles;
    rotatedRectangles = auxRotatedRectangles;
}

void ColorRecognizer::clear(){
    rectangles.clear();
    rotatedRectangles.clear();
    centers.clear();
}

void ColorRecognizer::setColorRange(ColorRange colorRange) {
    this->colorRange = colorRange;
}

std::vector<cv::Rect> ColorRecognizer::getRectangles() {
    return rectangles;
}

std::vector<cv::RotatedRect> ColorRecognizer::getRotatedRectangles() {
    return rotatedRectangles;
}

std::vector<cv::Point2f> ColorRecognizer::getCenters() {
    return centers;
}

ColorType ColorRecognizer::getColor() {
    return colorRange.colorType;
}

ColorRange ColorRecognizer::getColorRange() {
    return colorRange;
}

cv::Mat ColorRecognizer::getBinaryImage(){
    return binaryFrame;
}

cv::Mat ColorRecognizer::getTestImage(){
    return testImage;
}