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

    mtx.lock();
    send(robotRecognizer->getBlueRobots(),
         robotRecognizer->getYellowRobots(),
         robotRecognizer->getBall());
    mtx.unlock();

    dispatcher_update_gtkmm_frame.emit();
}

void VisionWindow::send(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {
    if(playing)
        stateSender->sendState(blueRobots, yellowRobots, ball);
}

void VisionWindow::updateGtkImage() {
    mtx.lock();
        cv::Mat _frame = frame.clone();
    mtx.unlock();

    mtx.lock();
        onRobotsNewPositions(robotRecognizer->getBlueRobots(),
                             robotRecognizer->getYellowRobots(),
                             robotRecognizer->getBall());
    mtx.unlock();

    screenImage->set_image(_frame, false);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

void VisionWindow::processFrame(cv::Mat _frame) {
    mtx.lock();
        Calibration _calibration = calibration;
    mtx.unlock();

    changeRotation(_frame, _calibration.rotation);

    if(_calibration.shouldCropImage){
        cropImage(_frame, _calibration.cut[0], _calibration.cut[1]);
    }

    map<ObjectType, ColorPosition> positions = getColorPosition(_frame);
    robotRecognizer->recognizeRobots(positions);

    mtx.lock();
        frame = _frame.clone();
    mtx.unlock();

}

std::map<ObjectType, ColorPosition> VisionWindow::getColorPosition(cv::Mat& _frame) {
    map<ObjectType, ColorPosition> whosePosition;
    std::vector<std::vector<cv::Rect> > drawRect;

    if (timerOptimization.timeOut(1000)) {
        for (auto colorRangeLoop : calibration.colorsRange) {
            ObjectType objectNameTeam = whoseColor[colorRangeLoop.colorType];

            if (objectNameTeam == ObjectType::Team) {
                colorRecognizer->setColorRange(colorRangeLoop);
                colorRecognizer->processImage(_frame, 3);

                ColorPosition colorTeam;
                colorTeam.color = colorRangeLoop.colorType;
                colorTeam.points = colorRecognizer->getCenters();

                whosePosition[objectNameTeam] = colorTeam;

                cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();

                drawRect.push_back(colorRecognizer->getRectangles());

                for (auto colorRangeRobot : calibration.colorsRange) {
                    ObjectType objectNameRobot = whoseColor[colorRangeRobot.colorType];

                    if (objectNameRobot == ObjectType::Robot1 || objectNameRobot == ObjectType::Robot2 || objectNameRobot == ObjectType::Robot3) {
                        ColorRecognizer colorRobot;
                        colorRobot.setColorRange(colorRangeRobot);
                        colorRobot.processImageInsideSectors(_frame, cutPosition[ colorRecognizer->getColor() ] , 30);

                        ColorPosition colorPositionRobot;
                        colorPositionRobot.color = colorRangeRobot.colorType;
                        colorPositionRobot.points = colorRobot.getCenters();

                        whosePosition[objectNameRobot] = colorPositionRobot;

                        cutPosition[ colorRobot.getColor() ] = colorRobot.getRectangles();

                        drawRect.push_back(colorRobot.getRectangles());
                    }
                }
            }

            if (objectNameTeam == ObjectType::Opponent) {
                ColorRecognizer colorRecognizerOpponent;
                colorRecognizerOpponent.setColorRange(colorRangeLoop);
                colorRecognizerOpponent.processImage(_frame, 3);

                ColorPosition colorPositionOpponent;
                colorPositionOpponent.color = colorRangeLoop.colorType;
                colorPositionOpponent.points = colorRecognizerOpponent.getCenters();

                whosePosition[objectNameTeam] = colorPositionOpponent;

                cutPosition[ colorRecognizerOpponent.getColor() ] = colorRecognizerOpponent.getRectangles();

                drawRect.push_back(colorRecognizerOpponent.getRectangles());
            }

            if (objectNameTeam == ObjectType::Ball) {
                ColorRecognizer colorRecognizerBall;
                colorRecognizerBall.setColorRange(colorRangeLoop);
                colorRecognizerBall.processImage(_frame, 1);

                ColorPosition colorPositionBall;
                colorPositionBall.color = colorRangeLoop.colorType;
                colorPositionBall.points = colorRecognizerBall.getCenters();

                whosePosition[objectNameTeam] = colorPositionBall;

                cutPosition[ colorRecognizerBall.getColor() ] = colorRecognizerBall.getRectangles();

                drawRect.push_back(colorRecognizerBall.getRectangles());
            }
        }

    } else {
        for (auto colorRange : calibration.colorsRange) {
            ObjectType objectName = whoseColor[colorRange.colorType];

            if (objectName == ObjectType::Team) {
                colorRecognizer->setColorRange(colorRange);
                colorRecognizer->processImageInsideSectors(_frame, cutPosition[ colorRecognizer->getColor() ] , 50);

                ColorPosition colorPosition;
                colorPosition.color = colorRange.colorType;
                colorPosition.points = colorRecognizer->getCenters();

                whosePosition[objectName] = colorPosition;

                cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();

                drawRect.push_back(colorRecognizer->getRectangles());

                for (auto colorRangeRobot : calibration.colorsRange) {
                    ObjectType objectNameRobot = whoseColor[colorRangeRobot.colorType];

                    if (objectNameRobot == ObjectType::Robot1 || objectNameRobot == ObjectType::Robot2 || objectNameRobot == ObjectType::Robot3) {
                        ColorRecognizer colorRobot;
                        colorRobot.setColorRange(colorRangeRobot);
                        colorRobot.processImageInsideSectors(_frame, cutPosition[ colorRecognizer->getColor() ] , 50);

                        ColorPosition colorPositionRobot;
                        colorPositionRobot.color = colorRangeRobot.colorType;
                        colorPositionRobot.points = colorRobot.getCenters();

                        whosePosition[objectNameRobot] = colorPositionRobot;

                        cutPosition[ colorRobot.getColor() ] = colorRobot.getRectangles();

                        drawRect.push_back(colorRobot.getRectangles());
                    }
                }
            }

            if (objectName == ObjectType::Ball || objectName == ObjectType::Opponent) {
                colorRecognizer->setColorRange(colorRange);
                colorRecognizer->processImageInsideSectors(_frame, cutPosition[ colorRecognizer->getColor() ] , 50);

                ColorPosition colorPosition;
                colorPosition.color = colorRange.colorType;
                colorPosition.points = colorRecognizer->getCenters();

                whosePosition[objectName] = colorPosition;

                cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();

                drawRect.push_back(colorRecognizer->getRectangles());
            }
        }
    }

    for (unsigned int i = 0; i < drawRect.size(); i++ ){
        drawRectangle(_frame, drawRect[i]);
    }

    return whosePosition;
}
