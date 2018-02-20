/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef I_CALIBRATION_REPOSITORY_H
#define I_CALIBRATION_REPOSITORY_H

#include <gtkmm/scale.h>
#include "Calibration.h"

class ICalibrationRepository {
public:
  virtual Calibration read(std::string pathName) = 0;
  virtual Calibration update(std::string pathName, Calibration calibration) = 0;
  virtual void remove(std::string pathName) = 0;
  virtual void create(std::string pathName, Calibration calibration) = 0;
};

#endif // I_CALIBRATION_REPOSITORY_H
