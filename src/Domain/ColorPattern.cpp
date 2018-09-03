//
// Created by rodetas on 18/08/18.
//

#include <ColorPattern.h>

ColorPattern::ColorPattern() {
    this->id = ObjectType::Unknown;
    this->singleColorType = ColorType::UnknownType;
    this->doubleColorType = ColorType::UnknownType;
    this->colorSide = ColorSide::UnknownSide;
}

ColorPattern::ColorPattern(ObjectType id, ColorType singleType, ColorType doubleType, ColorRange singleRange, ColorRange doubleRange, ColorSide colorSide) {
    this->id = id;
    this->singleColorType = singleType;
    this->doubleColorType = doubleType;
    this->singleColorRange = singleRange;
    this->doubleColorRange = doubleRange;
    this->colorSide = colorSide;
}

bool ColorPattern::isEquals(ColorPattern colorPattern) {
    return (colorPattern.doubleColorType == this->doubleColorType &&
            colorPattern.singleColorType == this->singleColorType &&
            colorPattern.colorSide == this->colorSide);
}
