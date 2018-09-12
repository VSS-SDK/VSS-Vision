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

    Calibration _calibration = calibration;

    image = changeRotation(image, _calibration.rotation);

    if(_calibration.shouldCropImage){
        image = cropImage(image, _calibration.cut[0], _calibration.cut[1]);
    }

    mtxUpdateFrame.lock();
    frame = image.clone();
    mtxUpdateFrame.unlock();

    recognizePattern(image);
}

/*
 * Transformar daqui para baixo em RobotRecognizer
 */

void VisionWindow::recognizeTeamColor(cv::Mat image) {
    ColorPattern teamPattern = pattern[ObjectType::Team];

    if (teamPattern.id == ObjectType::Team) {

        teamColorRecognizer->setColorRange(teamPattern.singleColorRange);

        if (timeOptimization.timeOut(1000)) {
            teamColorRecognizer->processImage(image);

        } else {
            teamColorRecognizer->processImageInSector(image, teamColorRecognizer->getRectangles());
        }
    }
}

void VisionWindow::recognizeRobotColor(cv::Mat image) {
    std::vector<cv::Rect> rect = teamColorRecognizer->getRectangles();
    std::vector<cv::RotatedRect> rotatedRect = teamColorRecognizer->getRotatedRectangles();

    for (unsigned int i = 0; i < rect.size(); i++) {

        cv::Mat cuttedImage = cropImage(image, rect[i], 0.3);
        rotatedRect[i] = increaseRotatedRect(rotatedRect[i], 1.8, 1.2);

        ColorRange colorRange1 (calibration.colorsRange, ColorType::Green);
        colorRecognizer1->setColorRange(colorRange1);
        colorRecognizer1->processImage(cuttedImage);
        colorRecognizer1->deleteOutsidePoint(rotatedRect[i], rect[i]);

        ColorRange colorRange2 (calibration.colorsRange, ColorType::Pink);
        colorRecognizer2->setColorRange(colorRange2);
        colorRecognizer2->processImage(cuttedImage);
        colorRecognizer2->deleteOutsidePoint(rotatedRect[i], rect[i]);

        //cout << "Green: " << colorRecognizer1->getCenters().size() << endl;
        //cout << "Pink: " << colorRecognizer2->getCenters().size() << endl;
    }

    frame = drawRectangle(image, rect);

}

void VisionWindow::recognizePattern(cv::Mat image) {
    recognizeTeamColor(image);
    recognizeRobotColor(image);
}

void VisionWindow::calculatePatternAngle(std::vector<cv::Point2f> position1, std::vector<cv::Point2f> position2, double &angleSingleColor, double &angleDoubleColor) {

    double dist1 = Math::distance(position2[0], position1[0]);
    double dist2 = Math::distance(position2[0], position1[1]);

    if (dist1 > dist2) {
        angleSingleColor = atan2(position2[0].y - position1[0].y, position2[0].x - position1[0].x) * (180 / M_PI) + 180;
        angleDoubleColor = atan2(position1[1].y - position1[0].y, position1[1].x - position1[0].x) * (180 / M_PI) + 180;

    } else {
        angleSingleColor = atan2(position2[0].y - position1[1].y, position2[0].x - position1[1].x) * (180 / M_PI) + 180;
        angleDoubleColor = atan2(position1[0].y - position1[1].y, position1[0].x - position1[1].x) * (180 / M_PI) + 180;
    }

    //cout << angleSingleColor << " - " << angleDoubleColor << endl;

}

void VisionWindow::calculateSideAngle(double angleSingleColor, double angleDoubleColor){
    double diff = angleSingleColor - angleDoubleColor;

    if (abs(diff) > 100){}


    if (diff > 30 && diff < 60) {

    } else if (diff < -30 && diff > -60) {

    }
}