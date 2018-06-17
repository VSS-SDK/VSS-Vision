/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::updateGtkImage() {
    processFrame();
    screenImage->set_image(frame);
}

void VisionWindow::receiveNewFrame(cv::Mat _frame) {
    frame = _frame;
    dispatcher_update_gtkmm_frame.emit();

    if(timeHelper.getElapsedTime() >= 1000){
        updateFpsLabel();

        timeHelper.restartCounting();
        fpsAmount = 0;
    } else {
        fpsAmount++;
    }

}

void VisionWindow::processFrame() {
  /*
    changeRotation(frame, calibration.rotation);

    if(calibration.shouldCropImage){
        cropImage(frame, calibration.cut[0], calibration.cut[1]);
    }

    map<ObjectType, ColorPosition> positions = getColorPosition();

    robotRecognizer->recognizeRobots(positions);

    signalRobotsNewPositions.emit(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());
    */
}

std::map<ObjectType, ColorPosition> VisionWindow::getColorPosition() {
    map<ObjectType, ColorPosition> whosePosition;
/*
    for (auto colorRange : calibration.colorsRange) {

        ObjectType objectName = whoseColor[colorRange.colorType];

        if (objectName != ObjectType::Unknown) {
            colorRecognizer->setColorRange(colorRange);
            colorRecognizer->processImage(frame);

            ColorPosition colorPosition;
            colorPosition.color = colorRange.colorType;
            colorPosition.points = colorRecognizer->getCenters();

            whosePosition[objectName] = colorPosition;

             TO DRAW IN IMAGE 
            auto rectangles = colorRecognizer->getRectangles();
            for (unsigned int i = 0; i < rectangles.size(); i++) {
                cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
            }
        }
    }
*/
    return whosePosition;
}
