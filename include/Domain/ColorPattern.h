//
// Created by rodetas on 18/08/18.
//

#ifndef VSS_VISION_ROBOTCOLORPATTERN_H
#define VSS_VISION_ROBOTCOLORPATTERN_H

#include <ColorType.h>
#include <ColorRange.h>
#include <ColorSide.h>
#include <ObjectType.h>

class ColorPattern {
public:

    ObjectType id;
    ColorType singleColorType;
    ColorType doubleColorType;
    ColorRange singleColorRange;
    ColorRange doubleColorRange;
    ColorSide colorSide;

    ColorPattern();
    ColorPattern(ObjectType, ColorType, ColorType, ColorRange, ColorRange, ColorSide);

    bool isEquals(ColorPattern colorPattern);
};

#endif //VSS_VISION_ROBOTCOLORPATTERN_H
