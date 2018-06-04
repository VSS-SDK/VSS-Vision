//
// Created by johnathan on 07/02/18.
//

#include "Point2d.h"

Point2d::Point2d() {
  x = 0.0;
  y = 0.0;
}

Point2d::Point2d(float x, float y) {
  this->x = x;
  this->y = y;
}

Point2d::Point2d(Point2d *point2d) {
  x = point2d->x;
  y = point2d->y;
}

std::ostream &operator<<(std::ostream &os, const Point2d &point2d) {
  os << "Point2d(" << point2d.x << ", " << point2d.y << ")";
  return os;
}
