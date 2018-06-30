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

    TimeHelper t;
    ColorPosition team = getOpponentPosition(_frame, ColorType::Blue);
    //std::vector<std::vector<ColorPosition>> team = getTeamPosition(_frame, ColorType::Blue);
    std::cout << t.getElapsedTime() << '\n';

    //map<ObjectType, ColorPosition> positions = getColorPosition(_frame);

    //robotRecognizer->recognizeRobots(positions);

    //signalRobotsNewPositions.emit(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());

    return _frame;
}

std::vector<std::vector<ColorPosition>> VisionWindow::getTeamPosition(cv::Mat& _frame, ColorType colorTeam){

    std::vector<vector<ColorPosition>> position;

    ColorRecognizer teamRecognizer;

    ColorRange teamRange = calibration.getColorRange(colorTeam);
    ColorRange pinkRange = calibration.getColorRange(ColorType::Pink);
    ColorRange greenRange = calibration.getColorRange(ColorType::Green);

    if (teamRange.colorType == colorTeam) {

        if (timerOptimization.timeOut(1000)) {
            teamRecognizer.setColorRange(teamRange);
            teamRecognizer.processImage(_frame);

        } else {
            teamRecognizer.setColorRange(teamRange);
            teamRecognizer.processImageInsideSectors(_frame, teamRectanglesCut , 50, 1);
        }

        teamRectanglesCut = teamRecognizer.getRectangles();

        for (unsigned int i = 0; i < teamRecognizer.getCenters().size(); i++) {

            std::vector<cv::Point2f> teamCentersVector;
                teamCentersVector.push_back( teamRecognizer.getCenters()[i] );

            std::vector<cv::Rect> teamRectanglesVector;
                teamRectanglesVector.push_back( teamRecognizer.getRectangles()[i] );

            ColorRecognizer greenRecognizer, pinkRecognizer;

            if (pinkRange.colorType == ColorType::Pink) {
                pinkRecognizer.setColorRange(pinkRange);
                pinkRecognizer.processImageInsideSectors(_frame, teamRectanglesVector , 50, 2);
            }

            if (greenRange.colorType == ColorType::Green) {
                greenRecognizer.setColorRange(greenRange);
                greenRecognizer.processImageInsideSectors(_frame, teamRectanglesVector , 50, 2);
            }

            drawRectangle(_frame, teamRectanglesVector);
            drawRectangle(_frame, pinkRecognizer.getRectangles());
            drawRectangle(_frame, greenRecognizer.getRectangles());

            vector<ColorPosition> aux;

            if (teamRecognizer.getCenters().size() > 0)
                aux.push_back( ColorPosition( teamRecognizer.getColor(), teamCentersVector ) );

            if (pinkRecognizer.getCenters().size() > 0)
                aux.push_back( ColorPosition( pinkRecognizer.getColor(), pinkRecognizer.getCenters() ) );

            if (greenRecognizer.getCenters().size() > 0)
                aux.push_back( ColorPosition( greenRecognizer.getColor(), greenRecognizer.getCenters() ) );

            position.push_back(aux);
        }
    }

    return position;
}

ColorPosition VisionWindow::getOpponentPosition(cv::Mat& _frame, ColorType colorOpponent){

    ColorRecognizer opponentRecognizer;

    ColorRange opponentRange = calibration.getColorRange(colorOpponent);

    if (opponentRange.colorType == colorOpponent) {

        if (timerOptimization.timeOut(1000)) {
            opponentRecognizer.setColorRange(opponentRange);
            opponentRecognizer.processImage(_frame);

        } else {
            opponentRecognizer.setColorRange(opponentRange);
            opponentRecognizer.processImageInsideSectors(_frame, opponentRectanglesCut , 50, 1);
        }

        opponentRectanglesCut = opponentRecognizer.getRectangles();

        drawRectangle(_frame, opponentRecognizer.getRectangles());


    }

    return ColorPosition(opponentRecognizer.getColor(), opponentRecognizer.getCenters());
}
