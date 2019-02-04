/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Calibration.h"

Calibration::Calibration(){
}

Calibration::Calibration(Calibration *calibration){
  colorsRange = calibration->colorsRange;
  cut = calibration->cut;
}

std::ostream& operator<<( std::ostream& os, const Calibration& calibration )
{
  os << std::endl;
  for(unsigned int i = 0 ; i < calibration.colorsRange.size() ; i++){
    os << calibration.colorsRange.at(i);
  }

  os << std::endl;
  for(unsigned int i = 0 ; i < calibration.cut.size() ; i++){
    os << calibration.cut.at(i);
  }

	return os;
}
