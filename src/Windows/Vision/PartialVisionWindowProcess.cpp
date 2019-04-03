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

    mutexFPS.lock();
        timeHelper.calculateFramesPerSecond();
    mutexFPS.unlock();
}

void VisionWindow::send(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {

    mutexFrame.lock();
        cv::Mat image = frame.clone();
    mutexFrame.unlock();

    if(playing) {
        vss::State state(ball, blueRobots, yellowRobots);
        stateSender->sendState(state);
    }
}

bool VisionWindow::emitUpdateGtkImage(){
    dispatcher_update_gtkmm_frame.emit();
    return true;
}

void VisionWindow::updateGtkImage() {
    mutexFrame.lock();
        cv::Mat image = frame.clone();
    mutexFrame.unlock();

    screenImage->setImage(image);

    mtxGetRobots.lock();
    mutexFPS.lock();
        updateLabel(timeHelper.getFramesPerSecond(), robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    mutexFPS.unlock();
    mtxGetRobots.unlock();
}

void VisionWindow::processFrame(cv::Mat image) {
    mutexCalibration.lock();
        Calibration processCalibration = calibration;
    mutexCalibration.unlock();
    
    mtxPattern.lock();
        std::vector<ColorPattern> processPattern = pattern;
    mtxPattern.unlock();

    if (not perspectiveMatrix.empty())
        image = changePerspective(image, perspectiveMatrix);

    patternRecognizer->setPatternVector(processPattern);
    patternRecognizer->setRangeVector(processCalibration.colorsRange);
    patternRecognizer->recognizeMainColorBall(image);
    patternRecognizer->recognizeMainColorTeam(image);
    patternRecognizer->recognizeMainColorOpponent(image);

    patternRecognizer->recognizeSecondColor(image);

    mtxGetRobots.lock();
    robotRecognizer->setImage(image);
    robotRecognizer->recognizeTeam(patternRecognizer->getTeamMainColorPosition(), patternRecognizer->getTeamSecondColorPosition(), pattern);
    robotRecognizer->recognizeOpponent(patternRecognizer->getOpponentMainColorPosition());
    robotRecognizer->recognizeBall(patternRecognizer->getBallMainColorPosition());

    image = drawRobot(image, robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    mtxGetRobots.unlock();

    mutexFrame.lock();
        frame = image.clone();
    mutexFrame.unlock();

    //frame = patternRecognizer->getImage();
}

cv::Mat VisionWindow::drawRobot(cv::Mat image, std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {

    std::string colorName = toDescription(patternRecognizer->getTeamMainColorPosition().color);

    for (auto position : patternRecognizer->getTeamRotatedRect() ) {
        image = drawRotatedRectangle(image, position,Scalar(255,255,255));
        insertText(image, colorName,cv::Point2f (position.center.x+15, position.center.y+15), colorRGB(colorName));
    }

    colorName = toDescription(patternRecognizer->getOpponentMainColorPosition().color);

    for (auto position : patternRecognizer->getOpponentRotatedRect() ) {
        image = drawRotatedRectangle(image, position, Scalar(255,255,255));
        insertText(image, colorName,cv::Point2f (position.center.x+15, position.center.y+15), colorRGB(colorName));
    }
    
    return image;
}