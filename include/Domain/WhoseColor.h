//
// Created by paulo on 06/05/18.
//

#ifndef VSS_VISION_WHOSECOLOR_H
#define VSS_VISION_WHOSECOLOR_H

#include <Domain/WhoseName.h>
#include <Domain/ColorType.h>

class WhoseColor {
public:
    WhoseName whoseName;
    ColorType colorType;

    WhoseColor(WhoseName whoseName, ColorType colorType);

    WhoseColor();

    WhoseName getWhoseName() const;

    void setWhoseName(WhoseName whoseName);

    ColorType getColorType() const;

    void setColorType(ColorType colorType);
};

#endif //VSS_VISION_WHOSECOLOR_H
