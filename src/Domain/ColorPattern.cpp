//
// Created by rodetas on 18/08/18.
//

#include <ColorPattern.h>

bool ColorPattern::isEquals(ColorPattern colorPattern) {
    return (colorPattern.id == this->id && colorPattern.doubleColor == this->doubleColor &&
            colorPattern.singleColor == this->singleColor && colorPattern.colorSide == this->colorSide);
}