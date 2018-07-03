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

    send(robotRecognizer->getBlueRobots(),
         robotRecognizer->getYellowRobots(),
         robotRecognizer->getBall());

         dispatcher_update_gtkmm_frame.emit();
}

void VisionWindow::send(std::vector<vss::Robot> blueRobots, std::vector<vss::Robot> yellowRobots, vss::Ball ball) {
    if(playing) {
        mtx.lock();
            stateSender->sendState(blueRobots, yellowRobots, ball);
        mtx.unlock();
    }
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

    if (timerOptimization.timeOut(1000)) {
        for (auto colorRange : calibration.colorsRange) {
            ObjectType objectName = whoseColor[colorRange.colorType];

            if (objectName != ObjectType::Unknown) {
                colorRecognizer->setColorRange(colorRange);
                colorRecognizer->processImage(_frame);

                ColorPosition colorPosition;
                colorPosition.color = colorRange.colorType;
                colorPosition.points = colorRecognizer->getCenters();
                whosePosition[objectName] = colorPosition;

                cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();
                drawRectangle(_frame, colorRecognizer->getRectangles());
            }
        }

    } else {
        for (auto colorRange : calibration.colorsRange) {
            ObjectType objectName = whoseColor[colorRange.colorType];

            if (objectName != ObjectType::Unknown) {
                colorRecognizer->setColorRange(colorRange);
                colorRecognizer->processImageInsideSectors(_frame, cutPosition[ colorRecognizer->getColor() ] , 50);

                ColorPosition colorPosition;
                colorPosition.color = colorRange.colorType;
                colorPosition.points = colorRecognizer->getCenters();

                whosePosition[objectName] = colorPosition;

                cutPosition[ colorRecognizer->getColor() ] = colorRecognizer->getRectangles();
                drawRectangle(_frame, colorRecognizer->getRectangles());
            }
        }
    }

    return whosePosition;
}
