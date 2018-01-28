/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Calibration.h"

Calibration::Calibration(){
  rotation = 0.0;
  brightness = 0.0;
  contrast = 0.0;
  saturation = 0.0;
  exposure = 0.0;
  gain = 0.0;

  for(int i = 0 ; i < 8 ; i++){
    float aux[3] = {0.0, 0.0, 0.0};
    colorsRange.push_back(new ColorRange(aux, aux));
  }

  for(int i = 0 ; i < 4 ; i++){
    cut.push_back(0.0);
  }
}

Calibration::Calibration(Calibration *calibration){
  rotation = calibration->rotation;
  brightness = calibration->brightness;
  contrast = calibration->contrast;
  saturation = calibration->saturation;
  exposure = calibration->exposure;
  gain = calibration->gain;

  colorsRange = calibration->colorsRange;
  cut = calibration->cut;
}

std::ostream& operator<<( std::ostream& os, const Calibration& calibration )
{
  os << "rotation: " << calibration.rotation << std::endl;
  os << "brightness: " << calibration.brightness << std::endl;
  os << "contrast: " << calibration.contrast << std::endl;
  os << "saturation: " << calibration.saturation << std::endl;
  os << "exposure: " << calibration.exposure << std:: endl;

  for(unsigned int i = 0 ; i < calibration.colorsRange.size() ; i++){
    os << calibration.colorsRange.at(i);
  }

  for(unsigned int i = 0 ; i < calibration.cut.size() ; i++){
    os << calibration.cut.at(i) << std::endl;
  }

	return os;
}
