#include <ColorRecognizer.h>

void ColorRecognizer::processImage(cv::Mat image) {
    frame = image.clone();

    binarizesImage();
    recognizesRectangles();
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

    cv::medianBlur(processed, processed, 3);

    binaryFrame = processed.clone();
}

void ColorRecognizer::recognizesRectangles() {
    rectangles.clear();
    rotatedRectangles.clear();

    std::vector< cv::Vec4i > hierarchy;
    std::vector< std::vector<cv::Point> > allContours;

    cv::findContours(binaryFrame.clone(), allContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // sort in crescent order the contours vector by found area
    sort(allContours.begin(), allContours.end(),
        [](const std::vector<cv::Point> c1, const std::vector<cv::Point> c2){
            return cv::contourArea(c1, false) > cv::contourArea(c2, false);
        }
    );

    // eliminate small noises
    std::vector< std::vector<cv::Point> > contours;
    for(unsigned int i = 0; i < allContours.size(); i++) {
        if ( cv::contourArea(allContours[i], false) > (cv::contourArea(allContours[0], false) * 0.5) ) {
            contours.push_back( allContours[i] );
        }
    }

    std::vector<cv::Rect> vectorRect( contours.size() );
    std::vector<cv::RotatedRect> vectorRotatedRect( contours.size() );
    std::vector<std::vector<cv::Point>> contours_poly( contours.size() );

    for(unsigned int i = 0; i < contours.size(); i++){
        vectorRotatedRect[i] = cv::minAreaRect( cv::Mat(contours[i]) );
        approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 0, true );
        vectorRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
        vectorRect[i].x -= 1;
        vectorRect[i].y -= 1;
        vectorRect[i].width  += 2;
        vectorRect[i].height += 2;
    }

    rectangles = vectorRect;
    rotatedRectangles = vectorRotatedRect;
}

void ColorRecognizer::calculateCenter(){
    centers.clear();

    for (auto r : rotatedRectangles) {
        centers.push_back(r.center);
    }
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