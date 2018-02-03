/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <gtkmm.h>
#include "GProgram.h"
#include "DirectoryHelper.h"
#include "Calibration.h"
#include "ICalibrationRepository.h"
#include "CalibrationRepository.h"

int main(int argc, char *argv[]) {
    ICalibrationRepository *calibrationRepository = new CalibrationRepository();
    cout << getCurrentWorkingDir() << endl;
    string path = getCurrentWorkingDir() + "/test.txt";

    calibrationRepository->create(path, new Calibration());

    auto calibration = calibrationRepository->read(path);
    // GProgram app;
    // app.run(argc, argv);
}
