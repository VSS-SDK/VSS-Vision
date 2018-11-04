//
// Created by rodetas on 18/08/18.
//

#ifndef VSS_VISION_ROBOTCOLORPATTERN_H
#define VSS_VISION_ROBOTCOLORPATTERN_H

#include <ColorType.h>
#include <ColorRange.h>
#include <ObjectType.h>

class ColorPattern {
public:

    ObjectType id;
    ColorType singleColorType;
    ColorRange singleColorRange;

    ColorPattern();
    ColorPattern(ObjectType, ColorType, ColorRange);

    friend bool operator==(const ColorPattern& a, const ColorPattern& b);

};

#endif //VSS_VISION_ROBOTCOLORPATTERN_H
