/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::receiveNewFrame(cv::Mat image) {
    processFrame(image.clone());

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
        cv::Mat image = frame.clone();
    mtxUpdateFrame.unlock();

    mtxGetRobots.lock();
        onRobotsNewPositions(robotRecognizer->getBlueRobots(),
                             robotRecognizer->getYellowRobots(),
                             robotRecognizer->getBall());
    mtxGetRobots.unlock();

    screenImage->set_image(image, false);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void VisionWindow::processFrame(cv::Mat image) {
   // mtx.lock();
        Calibration _calibration = calibration;
   // mtx.unlock();

    changeRotation(image, _calibration.rotation);

    if(_calibration.shouldCropImage){
        cropImage(image, _calibration.cut[0], _calibration.cut[1]);
    }

    mtxUpdateFrame.lock();
    frame = image.clone();
    mtxUpdateFrame.unlock();

    ColorPattern team = pattern[ObjectType::Team];


    if (team.id == ObjectType::Team) {
        colorRecognizer->setColorRange(team.singleColorRange);
        colorRecognizer->processImage(image);

        if (colorRecognizer->getImageFromColor().size() > 0){
            frame = colorRecognizer->getImageFromColor()[0];
        }

    }
}

std::map<ObjectType, ColorPosition> VisionWindow::getColorPosition(cv::Mat& image) {
    map<ObjectType, ColorPosition> whosePosition;
    return whosePosition;
}
