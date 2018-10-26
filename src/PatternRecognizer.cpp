/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "PatternRecognizer.h"

PatternRecognizer::PatternRecognizer() {
    ballColorRecognizer = new ColorRecognizer;
    teamColorRecognizer = new ColorRecognizer;
    opponentColorRecognizer = new ColorRecognizer;
    colorRecognizer1 = new ColorRecognizer;
    colorRecognizer2 = new ColorRecognizer;
}

void PatternRecognizer::setPatternVector(std::vector<ColorPattern> p) {
    pattern = p;
}

void PatternRecognizer::setRangeVector(std::vector<ColorRange> r) {
    range = r;
}

void PatternRecognizer::recognizeMainColorBall(cv::Mat image) {
    if (pattern[ObjectType::Ball].id == ObjectType::Ball) {
        ballColorRecognizer->setColorRange(pattern[ObjectType::Ball].singleColorRange);

        if (timeBall.timeOut(1000)) {
            ballColorRecognizer->processImage(image, 1);
        } else {
            ballColorRecognizer->processImageInSector(image, ballColorRecognizer->getRectangles(), 1);
        }
    }
}

void PatternRecognizer::recognizeMainColorTeam(cv::Mat image) {
    if (pattern[ObjectType::Team].id == ObjectType::Team) {
        teamColorRecognizer->setColorRange(pattern[ObjectType::Team].singleColorRange);

        if (timeTeam.timeOut(1000)) {
            teamColorRecognizer->processImage(image, 3);
        } else {
            teamColorRecognizer->processImageInSector(image, teamColorRecognizer->getRectangles(), 3);
        }
    }
}

void PatternRecognizer::recognizeMainColorOpponent(cv::Mat image) {
    if (pattern[ObjectType::Opponent].id == ObjectType::Opponent) {
        opponentColorRecognizer->setColorRange(pattern[ObjectType::Opponent].singleColorRange);

        if (timeOpponent.timeOut(1000)) {
            opponentColorRecognizer->processImage(image, 3);
        } else {
            opponentColorRecognizer->processImageInSector(image, opponentColorRecognizer->getRectangles(), 3);
        }
    }
}

void PatternRecognizer::recognizeSecondColor(cv::Mat image) {
    std::vector<cv::Rect> teamRect = teamColorRecognizer->getRectangles();
    std::vector<cv::RotatedRect> teamRotatedRect = teamColorRecognizer->getRotatedRectangles();

    std::vector<ColorPosition> aux = playerColorPosition;
    playerColorPosition.clear();

    for (unsigned int i = 0; i < teamRect.size(); i++) {
        teamRect[i] = increaseRect(image, teamRect[i], 0.5, 0.5);
        teamRotatedRect[i] = increaseRotatedRect(image, teamRotatedRect[i], 2, 1.2);

        cv::Mat cuttedImage = cropImage(image, teamRect[i]);

        ColorRange colorRange1 (range, ColorType::Green);
        colorRecognizer1->setColorRange(colorRange1);
        colorRecognizer1->processImage(cuttedImage, 3);
        //colorRecognizer1->deleteOutsidePoint(teamRotatedRect[i], teamRect[i]);

        ColorRange colorRange2 (range, ColorType::Pink);
        colorRecognizer2->setColorRange(colorRange2);
        colorRecognizer2->processImage(cuttedImage, 3);
        //colorRecognizer2->deleteOutsidePoint(teamRotatedRect[i], teamRect[i]);

        if (colorRecognizer1->getCenters().size() == 3) {
            ColorPosition position;
            position.color = colorRecognizer1->getColor();
            position.points = colorRecognizer1->getCenters();
            playerColorPosition.push_back (position);
        } else {
            //std::cout << "Green color founded: " << colorRecognizer1->getCenters().size() << std::endl;
        }

        if (colorRecognizer2->getCenters().size() == 3){
            ColorPosition position;
            position.color = colorRecognizer2->getColor();
            position.points = colorRecognizer2->getCenters();
            playerColorPosition.push_back(position);
        } else {
            std::cout << "Pink color founded: " << colorRecognizer2->getCenters().size() << std::endl;
        }

        testImage = colorRecognizer2->getBinaryImage();

        i = teamRect.size();
    }
    testRect = teamRect;
    testRotatedRect = teamRotatedRect;
}

cv::Mat PatternRecognizer::getImage() {
    return testImage;
}
std::vector<cv::Rect> PatternRecognizer::getRect() {
    return testRect;
}

std::vector<cv::RotatedRect> PatternRecognizer::getRotatedRect() {
    return testRotatedRect;
}

ColorPosition PatternRecognizer::getBallMainColorPosition() {
    ColorPosition position;
    position.color = ballColorRecognizer->getColor();
    position.points = ballColorRecognizer->getCenters();
    return position;
}

ColorPosition PatternRecognizer::getTeamMainColorPosition() {
    ColorPosition position;
    position.color = teamColorRecognizer->getColor();
    position.points = teamColorRecognizer->getCenters();
    return position;
}

ColorPosition PatternRecognizer::getOpponentMainColorPosition() {
    ColorPosition position;
    position.color = opponentColorRecognizer->getColor();
    position.points = opponentColorRecognizer->getCenters();
    return position;
}

std::vector<ColorPosition> PatternRecognizer::getTeamSecondColorPosition() {
    return playerColorPosition;
}

std::vector<cv::RotatedRect> PatternRecognizer::getBallRotatedRect() {
    return ballColorRecognizer->getRotatedRectangles();
}

std::vector<cv::RotatedRect> PatternRecognizer::getTeamRotatedRect() {
    return teamColorRecognizer->getRotatedRectangles();
}

std::vector<cv::RotatedRect> PatternRecognizer::getOpponentRotatedRect() {
    return opponentColorRecognizer->getRotatedRectangles();
}