/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "ColorRange.h"

ColorRange::ColorRange(){
  colorType = ColorType::UnknownType;
  for(int i = 0 ; i < 3 ; i++){
    this->min[i] = 0.0;
    this->max[i] = 0.0;
  }
}

ColorRange::ColorRange(float *min, float *max){
  colorType = ColorType::UnknownType;
  for(int i = 0 ; i < 3 ; i++){
    this->min[i] = min[i];
    this->max[i] = max[i];
  }
}

ColorRange::ColorRange( ColorRange *colorRange ){
  colorType = colorRange->colorType;
  for(int i = 0 ; i < 3 ; i++){
    min[i] = colorRange->min[i];
    max[i] = colorRange->max[i];
  }
}
std::ostream& operator<<( std::ostream& os, const ColorRange& colorRange )
{
  os << "colorType: " << colorRange.colorType << std::endl;
  os << "min: (" << colorRange.min[0] << ", " << colorRange.min[1] << ", " << colorRange.min[2] << ")" << std::endl;
  os << "max: (" << colorRange.max[0] << ", " << colorRange.max[1] << ", " << colorRange.max[2] << ")" << std::endl;

  return os;
}
