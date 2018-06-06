//
// Created by johnathan on 07/02/18.
//

#ifndef VSS_VISION_POINT2D_H
#define VSS_VISION_POINT2D_H

#include "iostream"

class Point2d{
public:
    float x;
    float y;

    Point2d();
    Point2d(float x, float y);
    Point2d(Point2d*);

    friend std::ostream& operator<<( std::ostream& os, const Point2d& point2d );
};

#endif //VSS_VISION_POINT2D_H
