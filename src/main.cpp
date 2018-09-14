/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Windows/Menu/MenuWindow.h"
#include "Windows/Vision/VisionWindow.h"
#include "Windows/Calibration/CalibrationWindow.h"
#include <Domain/ExecutionConfig.h>
#include <Builders/StdinInterpreterBuilder.h>

vss::ExecutionConfig loadExecutionConfig(int argc, char** argv){
    auto stdinInterpreterBuilder = new vss::StdinInterpreterBuilder();

    stdinInterpreterBuilder
            ->onStateSendAddr()
            ->onStatePort();

    auto stdinInterpreter = stdinInterpreterBuilder->buildInterpreter();

    return stdinInterpreter->extractExecutionConfig(argc, argv);
}

int main(int argc, char *argv[]) {
    auto exeConfig = loadExecutionConfig(argc, argv);

    if(!exeConfig.isValidConfiguration)
        return 0;

    Gtk::Main kit(argc, argv);

    int programState = MENU;

    while (programState != EXIT){
        switch (programState){

            case MENU : {
                IMenuWindow *menuWindow = new MenuWindow();
                programState = menuWindow->run(argc, argv);
            } break;

            case VISION : {
                IVisionWindow *visionWindow = new VisionWindow(exeConfig);
                programState = visionWindow->run(argc, argv);
            } break;

            case CALIBRATION : {
                ICalibrationWindow *calibrationWindow = new CalibrationWindow();
                programState = calibrationWindow->run(argc, argv);
            } break;
        }
    }
}