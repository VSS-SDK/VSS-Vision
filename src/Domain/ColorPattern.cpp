//
// Created by rodetas on 18/08/18.
//

#include <ColorPattern.h>

ColorPattern::ColorPattern() {
    this->id = ObjectType::Unknown;
    this->doubleColor = ColorType::UnknownType;
    this->singleColor = ColorType::UnknownType;
    this->colorSide = ColorSide::UnknownSide;
}

ColorPattern::ColorPattern(ObjectType id, ColorType doubleColor, ColorType singleColor, ColorSide colorSide) {
    this->id = id;
    this->doubleColor = doubleColor;
    this->singleColor = singleColor;
    this->colorSide = colorSide;
}

bool ColorPattern::isEquals(ColorPattern colorPattern) {
    return (colorPattern.id == this->id && colorPattern.doubleColor == this->doubleColor &&
            colorPattern.singleColor == this->singleColor && colorPattern.colorSide == this->colorSide);
}
