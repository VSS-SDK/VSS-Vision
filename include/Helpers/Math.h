//
// Created by manoel on 21/05/18.
//

#ifndef VSS_VISION_MATH_H
#define VSS_VISION_MATH_H

#include <cxcore.h>

class Math {

public:
    static double distance(cv::Point2f, cv::Point2f);
    static cv::Point midPoint(cv::Point, cv::Point);

};

#endif //VSS_VISION_MATH_H
