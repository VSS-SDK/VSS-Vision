/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COLOR_RANGE_H
#define COLOR_RANGE_H

#include "iostream"
#include "ColorType.h"

class ColorRange {
public:
    ColorType colorType;
    float min[3];
    float max[3];

    ColorRange();
    ColorRange( float *min, float *max );
    ColorRange( ColorRange *colorRange );

    friend std::ostream& operator<<( std::ostream& os, const ColorRange& colorRange );
};

#endif // COLOR_RANGE_H
