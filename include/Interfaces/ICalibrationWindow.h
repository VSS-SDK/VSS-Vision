/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef IGPROGRAM_H_
#define IGPROGRAM_H_

class ICalibrationWindow {
public:
  virtual void run(int argc, char *argv[]) = 0;
};
#endif
