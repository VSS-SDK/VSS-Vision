//
// Created by rodetas on 18/08/18.
//

#ifndef VSS_VISION_COLORSIDE_H
#define VSS_VISION_COLORSIDE_H

#include <string>

enum ColorSide {
    UnknownSide = 0,
    Left = 1,
    Right = 2
};

std::string toDescription(ColorSide);

#endif //VSS_VISION_COLORSIDE_H
