//
// Created by manoel on 21/05/18.
//

#ifndef VSS_VISION_MATH_H
#define VSS_VISION_MATH_H

#include "opencv/highgui.h"

class Math {

public:
    static double distance(cv::Point, cv::Point);
    static cv::Point midPoint(cv::Point, cv::Point);

};

#endif //VSS_VISION_MATH_H
