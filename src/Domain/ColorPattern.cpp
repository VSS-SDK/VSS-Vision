//
// Created by rodetas on 18/08/18.
//

#include <ColorPattern.h>

ColorPattern::ColorPattern() {
    this->id = ObjectType::Unknown;
    this->singleColorType = ColorType::UnknownType;
}

ColorPattern::ColorPattern(ObjectType id, ColorType singleType, ColorRange singleRange) {
    this->id = id;
    this->singleColorType = singleType;
    this->singleColorRange = singleRange;
}

bool operator==(const ColorPattern& a, const ColorPattern& b) {
    return (a.singleColorType == b.singleColorType);
}
