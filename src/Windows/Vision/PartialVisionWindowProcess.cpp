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
   // mtx.lock();
        Calibration _calibration = calibration;
   // mtx.unlock();

    image = changeRotation(image, _calibration.rotation);

    if(_calibration.shouldCropImage){
        image = cropImage(image, _calibration.cut[0], _calibration.cut[1]);
    }

    mtxUpdateFrame.lock();
    frame = image.clone();
    mtxUpdateFrame.unlock();

    recognizeTeamColor(image);
    recognizeRobotColor(image);
}

void VisionWindow::recognizeTeamColor(cv::Mat image) {
    ColorPattern teamPattern = pattern[ObjectType::Team];

    if (teamPattern.id == ObjectType::Team) {
        teamColorRecognizer->setColorRange(teamPattern.singleColorRange);
        teamColorRecognizer->processImage(image);
    }
}

void VisionWindow::recognizeRobotColor(cv::Mat image) {
    std::vector<cv::Rect> rect = teamColorRecognizer->getRectangles();
    std::vector<cv::RotatedRect> rotatedRect = teamColorRecognizer->getRotatedRectangles();

    for (unsigned int i = 0; i < teamColorRecognizer->getRectangles().size(); i++) {

        // change coordinate
        rotatedRect[i].center.x = abs(rotatedRect[i].center.x - rect[i].x);
        rotatedRect[i].center.y = abs(rotatedRect[i].center.y - rect[i].y);

        cv::Mat cuttedImage = cropImage(image, rect[i], 0);

        ColorRange colorRange1 (calibration.colorsRange, ColorType::Pink);
        colorRecognizer1->setColorRange(colorRange1);
        colorRecognizer1->processImage(cuttedImage);
        colorRecognizer1->deleteOutsidePoint(rotatedRect[i]);

        ColorRange colorRange2 (calibration.colorsRange, ColorType::Green);
        colorRecognizer2->setColorRange(colorRange2);
        colorRecognizer2->processImage(cuttedImage);
        colorRecognizer2->deleteOutsidePoint(rotatedRect[i]);

        frame = cuttedImage;
        recognizePattern();
    }
}

void VisionWindow::recognizePattern() {

    std::vector<cv::Point2f> color1Position = colorRecognizer1->getCenters();
    std::vector<cv::Point2f> color2Position = colorRecognizer2->getCenters();

    if (!color1Position.empty() && !color2Position.empty()) {


        ColorPattern recognize;

        unsigned long int color1Amount = colorRecognizer1->getRectangles().size();
        unsigned long int color2Amount = colorRecognizer2->getRectangles().size();

        double angleSingleColor;
        double angleDoubleColor;

        if (color1Amount > 1) {
            recognize.singleColorType = ColorType::Green;
            recognize.doubleColorType = ColorType::Pink;

            calculatePatternAngle(color1Position, color2Position, angleSingleColor, angleDoubleColor);

        } else if (color2Amount > 1) {
            recognize.singleColorType = ColorType::Pink;
            recognize.doubleColorType = ColorType::Green;

            calculatePatternAngle(color2Position, color1Position, angleSingleColor, angleDoubleColor);

        }

        for (int i = ObjectType::Robot1; i >= ObjectType::Robot3; i++) {
            if (recognize.isEquals(pattern[i])) {
                recognize.id = pattern[i].id;
            }
        }
    }
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
}

void VisionWindow::calculateSideAngle(double angleSingleColor, double angleDoubleColor){
    double diff = angleSingleColor - angleDoubleColor;

    if (abs(diff) > 100){}

    
    if (diff > 30 && diff < 60) {

    } else if (diff < -30 && diff > -60) {

    }
}