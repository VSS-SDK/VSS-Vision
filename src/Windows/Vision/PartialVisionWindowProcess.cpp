/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::receiveNewFrame(cv::Mat _frame) {
    processFrame(_frame.clone());

    mtxGetRobots.lock();
    send(robotRecognizer->getBlueRobots(),
         robotRecognizer->getYellowRobots(),
         robotRecognizer->getBall());
    mtxGetRobots.unlock();

    dispatcher_update_gtkmm_frame.emit();
}

void VisionWindow::send(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {
    if(playing)
        stateSender->sendState(blueRobots, yellowRobots, ball);
}

void VisionWindow::updateGtkImage() {
    mtxUpdateFrame.lock();
        cv::Mat _frame = frame.clone();
    mtxUpdateFrame.unlock();

    mtxGetRobots.lock();
        onRobotsNewPositions(robotRecognizer->getBlueRobots(),
                             robotRecognizer->getYellowRobots(),
                             robotRecognizer->getBall());
    mtxGetRobots.unlock();

    screenImage->set_image(_frame, false);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void VisionWindow::processFrame(cv::Mat _frame) {
   // mtx.lock();
        Calibration _calibration = calibration;
   // mtx.unlock();

    changeRotation(_frame, _calibration.rotation);

    if(_calibration.shouldCropImage){
        cropImage(_frame, _calibration.cut[0], _calibration.cut[1]);
    }

//    map<ObjectType, ColorPosition> positions = getColorPosition(_frame);
//    robotRecognizer->recognizeRobots(positions);

    mtxUpdateFrame.lock();
        frame = _frame.clone();
    mtxUpdateFrame.unlock();

}

std::map<ObjectType, ColorPosition> VisionWindow::getColorPosition(cv::Mat& _frame) {
    map<ObjectType, ColorPosition> whosePosition;
    return whosePosition;
}
