//
// Created by manoel on 21/05/18.
//

#ifndef VSS_VISION_MATH_H
#define VSS_VISION_MATH_H

#include <opencv/cxcore.h>

class Math {

public:
    static double distance(cv::Point, cv::Point);
    static cv::Point midPoint(cv::Point, cv::Point);
    static double angle(cv::Point, cv::Point);
    static double constrainAngle(double);

};

#endif //VSS_VISION_MATH_H
