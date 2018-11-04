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


    for (uint i = 0; i < blueRobots.size(); i++) {
        std::cout << blueRobots[i] << std::endl;
    }

    mtxUpdateFrame.lock();
        cv::Mat image = frame.clone();
    mtxUpdateFrame.unlock();

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

    screenImage->setImage(image);

    mtxGetRobots.lock();
    mtxFps.lock();
        updateLabel(timeHelper.getFramesPerSecond(), robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    mtxFps.unlock();
    mtxGetRobots.unlock();

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
    patternRecognizer->recognizeMainColorBall(image);
    patternRecognizer->recognizeMainColorTeam(image);
    patternRecognizer->recognizeMainColorOpponent(image);

    patternRecognizer->recognizeSecondColor(image);

    robotRecognizer->setImage(image);
    robotRecognizer->recognizeTeam(patternRecognizer->getTeamMainColorPosition(), patternRecognizer->getTeamSecondColorPosition(), pattern);
    robotRecognizer->recognizeOpponent(patternRecognizer->getOpponentMainColorPosition());
    robotRecognizer->recognizeBall(patternRecognizer->getBallMainColorPosition());

    for (auto r : patternRecognizer->getBallRotatedRect()) {
        r.angle = 0;
        image = drawRotatedRectangle(image, r);
    }

    for (auto r : patternRecognizer->getOpponentRotatedRect()) {
        image = drawRotatedRectangle(image, r);
    }

    for (auto r : patternRecognizer->getTeamRotatedRect()) {
        image = drawRotatedRectangle(image, r);
    }

    /*
    mtxGetRobots.lock();
        if (pattern[ObjectType::Team].singleColorType == ColorType::Blue) {
            for (auto robot : robotRecognizer->getBlueRobots()) {
                cv::RotatedRect r(cv::Point2f(robot.x, robot.y), cv::Size2f(20,20), robot.angle);
                image = drawRotatedRectangle(image, r);
            }

        } else {
            for (auto robot : robotRecognizer->getBlueRobots()) {
                cv::RotatedRect r(cv::Point2f(robot.x, robot.y), cv::Size2f(20,20), robot.angle);
                image = drawRotatedRectangle(image, r);

            }

        }
    mtxGetRobots.unlock();
    */

    std::cout << std::endl;


    mtxUpdateFrame.lock();
        frame = image.clone();
    mtxUpdateFrame.unlock();

    //frame = patternRecognizer->getImage();


}