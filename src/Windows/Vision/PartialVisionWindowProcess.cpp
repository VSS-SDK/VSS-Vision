/*
* This file is part of the VSS-Vision project.
*
* This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
* v. 3.0. If a copy of the GPL was not distributed with this
* file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
*/

#include <Windows/Vision/VisionWindow.h>

void VisionWindow::receiveNewFrame(cv::Mat _frame) {
    frame = _frame.clone();
    dispatcher_update_gtkmm_frame.emit();
}

void VisionWindow::updateGtkImage() {
    cv::Mat processedFrame = processFrame(frame.clone());
    screenImage->set_image(processedFrame);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

cv::Mat VisionWindow::processFrame(cv::Mat _frame) {
    changeRotation(_frame, calibration.rotation);

    if(calibration.shouldCropImage){
        cropImage(_frame, calibration.cut[0], calibration.cut[1]);
    }

    std::vector<ColorPosition> blue = getBluePosition(_frame);
    //map<ObjectType, ColorPosition> positions = getColorPosition(_frame);

    //robotRecognizer->recognizeRobots(positions);

    //signalRobotsNewPositions.emit(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());

    return _frame;
}

std::vector<ColorPosition> VisionWindow::getBluePosition(cv::Mat& _frame){

    ColorRecognizer blueRecognizer, greenRecognizer, pinkRecognizer;

    ColorRange blueRange = calibration.getColorRange(ColorType::Blue);
    ColorRange pinkRange = calibration.getColorRange(ColorType::Red);
    ColorRange greenRange = calibration.getColorRange(ColorType::Green);

    if (blueRange.colorType == ColorType::Blue) {
        blueRecognizer.setColorRange(blueRange);
        blueRecognizer.processImage(_frame);

        if (pinkRange.colorType == ColorType::Red) {
            pinkRecognizer.setColorRange(pinkRange);
            pinkRecognizer.processImageInsideSectors(_frame, blueRecognizer.getRectangles() , 50);
        }

        if (greenRange.colorType == ColorType::Green) {
            greenRecognizer.setColorRange(greenRange);
            greenRecognizer.processImageInsideSectors(_frame, blueRecognizer.getRectangles() , 50);
        }

        drawRectangle(_frame, blueRecognizer.getRectangles());
        drawRectangle(_frame, pinkRecognizer.getRectangles());
        drawRectangle(_frame, greenRecognizer.getRectangles());
    }

    std::vector<ColorPosition> position;

    if (blueRecognizer.getCenters().size() > 0)
        position.push_back( ColorPosition( blueRecognizer.getColor(), blueRecognizer.getCenters() ) );

    if (pinkRecognizer.getCenters().size() > 0)
        position.push_back( ColorPosition( pinkRecognizer.getColor(), pinkRecognizer.getCenters() ) );

    if (greenRecognizer.getCenters().size() > 0)
        position.push_back( ColorPosition( greenRecognizer.getColor(), greenRecognizer.getCenters() ) );

    return position;
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
