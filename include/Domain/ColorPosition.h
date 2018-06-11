/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COLOR_POSITION_H
#define COLOR_POSITION_H

#include <vector>
#include <cxcore.h>
#include "ColorType.h"

class ColorPosition {
public:
    ColorType color;
    std::vector<cv::Point2f> points;

    ColorPosition(){
        color = ColorType::UnknownType;
    }
};

#endif // COLOR_POSITION_H
