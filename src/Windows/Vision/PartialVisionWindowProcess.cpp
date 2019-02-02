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

    // image = changeRotation(image, processCalibration.rotation);

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

    for (auto robot : blueRobots) {
        cv::RotatedRect r;
        r.angle = robot.angle;
        r.size = cv::Point2f(image.cols*0.05, image.cols*0.05);
        r.center.x = int ((robot.x * image.cols) / 170);
        r.center.y = int ((robot.y * image.rows) / 130);

        image = drawRotatedRectangle(image, r);
    }

    for (auto robot : yellowRobots) {
        cv::RotatedRect r;
        r.angle = robot.angle;
        r.size = cv::Point2f(image.cols*0.05, image.cols*0.05);
        r.center.x = int ((robot.x * image.cols) / 170);
        r.center.y = int ((robot.y * image.rows) / 130);

        image = drawRotatedRectangle(image, r);
    }

    cv::RotatedRect r;
    r.angle = 0;
    r.size = cv::Point2f(image.cols*0.02, image.cols*0.02);
    r.center.x = (ball.x * image.cols) / 170;
    r.center.y = (ball.y * image.rows) / 130;

    image = drawRotatedRectangle(image, r);

    return image;
}