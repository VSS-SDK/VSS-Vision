//
// Created by paulo on 06/05/18.
//

#include "WhoseColor.h"


WhoseColor::WhoseColor(WhoseName whoseName, ColorType colorType) : whoseName(whoseName), colorType(colorType) {}

WhoseColor::WhoseColor() {}

WhoseName WhoseColor::getWhoseName() const {
    return whoseName;
}

void WhoseColor::setWhoseName(WhoseName whoseName) {
    WhoseColor::whoseName = whoseName;
}

ColorType WhoseColor::getColorType() const {
    return colorType;
}

void WhoseColor::setColorType(ColorType colorType) {
    WhoseColor::colorType = colorType;
}
