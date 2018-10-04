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
        send(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    mtxGetRobots.unlock();

    mtxFps.lock();
        timeHelper.calculateFramesPerSecond();
    mtxFps.unlock();
}

void VisionWindow::send(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {
    if(playing)
        stateSender->sendState(blueRobots, yellowRobots, ball);
}

bool VisionWindow::emitUpdateGtkImage(){
    dispatcher_update_gtkmm_frame.emit();
    return true;
}

void VisionWindow::updateGtkImage() {
    mtxUpdateFrame.lock();
        cv::Mat image = frame.clone();
    mtxUpdateFrame.unlock();

    /*
    mtxGetRobots.lock();
        onRobotsNewPositions(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    mtxGetRobots.unlock();
    */

    screenImage->set_image(image);

    mtxFps.lock();
        updateLabel(timeHelper.getFramesPerSecond());
    mtxFps.unlock();
}

void VisionWindow::processFrame(cv::Mat image) {
    mtxCalibration.lock();
        Calibration processCalibration = calibration;
    mtxCalibration.unlock();
    
    mtxPattern.lock();
        std::vector<ColorPattern> processPattern = pattern;
    mtxPattern.unlock();

    // image = changeRotation(image, processCalibration.rotation);
    
    if(processCalibration.shouldCropImage){
        image = cropImage(image, processCalibration.cut[0], processCalibration.cut[1]);
    }

    patternRecognizer->setPatternVector(processPattern);
    patternRecognizer->setRangeVector(processCalibration.colorsRange);

    TimeHelper t;
    patternRecognizer->recognizeMainColor(image, ObjectType::Ball);
    patternRecognizer->recognizeMainColor(image, ObjectType::Team);
    patternRecognizer->recognizeMainColor(image, ObjectType::Opponent);
    
    patternRecognizer->recognizeSecondColor(image);
    std::cout << t.getElapsedTime() << std::endl;

    robotRecognizer->recognizeTeam(patternRecognizer->getTeamColorPosition(), patternRecognizer->getPlayerColorPosition(), pattern);
    robotRecognizer->recognizeOpponent(patternRecognizer->getOpponnetColorPosition());
    robotRecognizer->recognizeBall(patternRecognizer->getBallColorPosition());

    for (auto r : patternRecognizer->getBallRotatedRect()) {
        image = drawRotatedRectangle(image, r);
    }

    for (auto r : patternRecognizer->getOpponentRotatedRect()) {
        image = drawRotatedRectangle(image, r);
    }

    for (auto r : patternRecognizer->getTeamRotatedRect()) {
        image = drawRotatedRectangle(image, r);
    }
    
    mtxUpdateFrame.lock();
        frame = image.clone();
    mtxUpdateFrame.unlock();
}