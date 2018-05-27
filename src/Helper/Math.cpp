//
// Created by manoel on 21/05/18.
//

#include "Helpers/Math.h"

double Math::distance(cv::Point p1, cv::Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

cv::Point Math::midPoint(cv::Point p1, cv::Point p2){
    return cv::Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);
}