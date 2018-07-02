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
    screenImage->set_image(processedFrame, false);
    updateFpsLabel( timeHelper.framesPerSecond() );
}

cv::Mat VisionWindow::processFrame(cv::Mat _frame) {
    changeRotation(_frame, calibration.rotation);

    if(calibration.shouldCropImage){
        cropImage(_frame, calibration.cut[0], calibration.cut[1]);
    }

    ColorPosition ball = getBallPosition(_frame.clone(), ColorType::Orange);
    ColorPosition opponent = getOpponentPosition(_frame.clone(), whoseColor[ObjectType::Opponent]);
    std::vector<std::vector<ColorPosition>> team = getTeamPosition(_frame, whoseColor[ObjectType::Team]);

    robotRecognizer->recognizeBall(ball);
    robotRecognizer->recognizeTeam(team, whoseColor[ObjectType::Team]);
    robotRecognizer->recognizeOpponent(opponent, whoseColor[ObjectType::Opponent]);

    signalRobotsNewPositions.emit(robotRecognizer->getBlueRobots(), robotRecognizer->getYellowRobots(), robotRecognizer->getBall());

    for (auto draw : drawRectangleVector) {
        drawRectangle(_frame, draw);
    }
    drawRectangleVector.clear();

    return _frame;
}

std::vector<std::vector<ColorPosition>> VisionWindow::getTeamPosition(cv::Mat _frame, ColorType colorTeam){

    std::vector<vector<ColorPosition>> position;

    ColorRecognizer teamRecognizer;

    ColorRange teamRange = calibration.getColorRange(colorTeam);
    ColorRange pinkRange = calibration.getColorRange(ColorType::Pink);
    ColorRange greenRange = calibration.getColorRange(ColorType::Green);

    if (teamRange.colorType == colorTeam) {

        if (timerTeam.timeOut(1000)) {
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

            drawRectangleVector.push_back(teamRectanglesVector);
            drawRectangleVector.push_back(pinkRecognizer.getRectangles());
            drawRectangleVector.push_back(greenRecognizer.getRectangles());

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

ColorPosition VisionWindow::getOpponentPosition(cv::Mat _frame, ColorType colorOpponent){

    ColorRecognizer opponentRecognizer;

    ColorRange opponentRange = calibration.getColorRange(colorOpponent);

    if (opponentRange.colorType == colorOpponent) {

        if (timerOpponent.timeOut(1000)) {
            opponentRecognizer.setColorRange(opponentRange);
            opponentRecognizer.processImage(_frame);

        } else {
            opponentRecognizer.setColorRange(opponentRange);
            opponentRecognizer.processImageInsideSectors(_frame, opponentRectanglesCut , 50, 1);
        }

        opponentRectanglesCut = opponentRecognizer.getRectangles();

        drawRectangleVector.push_back(opponentRecognizer.getRectangles());
    }

    return ColorPosition(opponentRecognizer.getColor(), opponentRecognizer.getCenters());
}

ColorPosition VisionWindow::getBallPosition(cv::Mat _frame, ColorType colorBall){
    ColorRecognizer ballRecognizer;

    ColorRange ballRange = calibration.getColorRange(colorBall);

    if (ballRange.colorType == colorBall) {

        if (timerBall.timeOut(1000)) {
            ballRecognizer.setColorRange(ballRange);
            ballRecognizer.processImage(_frame);

        } else {
            ballRecognizer.setColorRange(ballRange);
            ballRecognizer.processImageInsideSectors(_frame, ballRectanglesCut , 50, 1);
        }

        ballRectanglesCut = ballRecognizer.getRectangles();

        drawRectangleVector.push_back(ballRecognizer.getRectangles());
    }

    return ColorPosition(ballRecognizer.getColor(), ballRecognizer.getCenters());
}
