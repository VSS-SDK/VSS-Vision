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
    /*
        onRobotsNewPositions(robotRecognizer->getBlueRobots(),
                             robotRecognizer->getYellowRobots(),
                             robotRecognizer->getBall());
    */
    mtxGetRobots.unlock();

    screenImage->set_image(image);
    updateLabel( timeHelper.framesPerSecond() );
}

void VisionWindow::processFrame(cv::Mat image) {

    mtxUpdateFrame.lock();
        frame = image.clone();
    mtxUpdateFrame.unlock();

    mtxCalibration.lock();
        Calibration processCalibration = calibration;
    mtxCalibration.unlock();
    
    mtxPattern.lock();
        std::vector<ColorPattern> processPattern = pattern;
    mtxPattern.unlock();

    image = changeRotation(image, processCalibration.rotation);

    if(processCalibration.shouldCropImage){
        image = cropImage(image, processCalibration.cut[0], processCalibration.cut[1]);
    }

    patternRecognizer->setPatternVector(processPattern);
    patternRecognizer->setRangeVector(processCalibration.colorsRange);

    patternRecognizer->recognizeMainColor(image, ObjectType::Ball);
    patternRecognizer->recognizeMainColor(image, ObjectType::Team);
    patternRecognizer->recognizeMainColor(image, ObjectType::Opponent);
    patternRecognizer->recognizeSecondColor(image);

    robotRecognizer->recognizeTeam(patternRecognizer->getTeamColorPosition(), patternRecognizer->getPlayerColorPosition(), pattern);
    //robotRecognizer->recognizeOpponent(patternRecognizer->getOpponnetColorPosition());
    //robotRecognizer->recognizeBall(patternRecognizer->getBallColorPosition());

    //cout << "Blue:     " << robotRecognizer->getBlueRobots().size() << endl;
    //cout << "Yellow:   " << robotRecognizer->getYellowRobots().size() << endl;

    //cout << endl;
}