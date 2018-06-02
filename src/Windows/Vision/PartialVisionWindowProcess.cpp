/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::setNewFrame() {
    processFrame();
    screenImage->set_image(frame);
}

void VisionWindow::receiveNewFrame(cv::Mat _frame) {
    frame = _frame;
    signal_set_new_frame.emit();
}

void VisionWindow::processFrame() {
    cv::warpAffine(frame, frame, cv::getRotationMatrix2D(cv::Point2f(frame.cols/2, frame.rows/2), calibration.rotation, 1.0), frame.size());

    if(calibration.shouldCropImage){
        cv::Rect rect = cv::Rect(cv::Point((int)calibration.cut[0].x, (int)calibration.cut[0].y),
                cv::Point((int)calibration.cut[1].x, (int)calibration.cut[1].y));

        try{
            frame = frame(rect);
        } catch (std::exception& e){
            cout << "Exception cropping image" << endl;
        }
    }

    map<WhoseName, ColorPosition> positions = getColorPosition();

    robotRecognizer->recognizeRobots(positions);

    auto robots = robotRecognizer->getRobots();
    auto ball = robotRecognizer->getBall();

    stateSender->sendState(robots, ball);
}

std::map<WhoseName, ColorPosition> VisionWindow::getColorPosition() {
    map<WhoseName, ColorPosition> whosePosition;

    for (auto colorRange : calibration.colorsRange) {
        WhoseName objectName = whoseColor[colorRange.colorType];

        if (objectName != WhoseName::Unknown) {
            colorRecognizer->setColorRange(colorRange);
            colorRecognizer->processImage(frame);

            ColorPosition colorPosition;
            colorPosition.color = colorRange.colorType;
            colorPosition.points = colorRecognizer->getCenters();

            whosePosition[objectName] = colorPosition;

            /* TO DRAW IN IMAGE */
            auto rectangles = colorRecognizer->getRectangles();
            for (unsigned int i = 0; i < rectangles.size(); i++) {
                cv::rectangle(frame, rectangles.at(i), cv::Scalar(255, 255, 255), 1, 1, 0);
            }
        }
    }

    return whosePosition;
}