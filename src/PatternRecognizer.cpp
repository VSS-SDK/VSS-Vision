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
    colorRecognizer3 = new ColorRecognizer;

    colorRecognizer.resize(8);
}

void PatternRecognizer::setPatternVector(std::vector<ColorPattern> p) {
    objectsPattern = p;
}

void PatternRecognizer::setRangeVector(std::vector<ColorRange> r) {
    colorsRange = r;
}

void PatternRecognizer::recognizeMainColorBall(cv::Mat image) {
    if (objectsPattern[ObjectType::Ball].id == ObjectType::Ball) {
        ballColorRecognizer->setColorRange(objectsPattern[ObjectType::Ball].singleColorRange);

        if (timeBall.timeOut(50)) {
            ballColorRecognizer->processImage(image, 1);
        } else {
            ballColorRecognizer->processImageInSector(image, ballColorRecognizer->getRectangles(), 1);
        }
    }
}

void PatternRecognizer::recognizeMainColorTeam(cv::Mat image) {
    if (objectsPattern[ObjectType::Team].id == ObjectType::Team) {
        teamColorRecognizer->setColorRange(objectsPattern[ObjectType::Team].singleColorRange);

        if (timeTeam.timeOut(500)) {
            teamColorRecognizer->processImage(image, 3);
        } else {
            teamColorRecognizer->processImageInSector(image, teamColorRecognizer->getRectangles(), 1);
        }
    }
}

void PatternRecognizer::recognizeMainColorOpponent(cv::Mat image) {
    if (objectsPattern[ObjectType::Opponent].id == ObjectType::Opponent) {
        opponentColorRecognizer->setColorRange(objectsPattern[ObjectType::Opponent].singleColorRange);

        if (timeOpponent.timeOut(500)) {
            opponentColorRecognizer->processImage(image, 3);
        } else {
            opponentColorRecognizer->processImageInSector(image, opponentColorRecognizer->getRectangles(), 1);
        }
    }
}

void PatternRecognizer::recognizeSecondColor(cv::Mat image) {
    std::vector<cv::Rect> teamRect = teamColorRecognizer->getRectangles();

    playerColorPosition.clear();

    for (unsigned int i = 0; i < teamRect.size(); i++) {
        teamRect[i] = increaseRect(image, teamRect[i], 1.5, 1.5);
        cv::Mat cuttedImage = cropImage(image, teamRect[i]);

        cv::Point2f center = cv::Point2f(teamRect[i].x + teamRect[i].width/2, teamRect[i].y + teamRect[i].height/2);

        int cont=0;

        for (unsigned int j = 3; j < 7; j++){ //varre todas as possibilidades de cores

            for (unsigned int k = 0; k<colorPossibilities.size(); k++) {

                if (objectsPattern[j].singleColorType == colorPossibilities[k]) { //verifica se e uma cor valida

                    ColorRange colorRange(colorsRange, objectsPattern[j].singleColorType);

                    colorRecognizer[cont].setColorRange(colorRange); //seta o recognizer pras validas
                    colorRecognizer[cont].processImage(cuttedImage, 1);

                    cont++; //conta as cores validas
                }
            }
        }

        float minDistance = 10000;

        ColorPosition position;

        for (int k = 0; k < cont; k++) {
            for (unsigned int j = 0; j < colorRecognizer[k].getCenters().size(); j++) {
                cv::Point2f point(colorRecognizer[k].getCenters()[j].x + teamRect[i].x,
                                  colorRecognizer[k].getCenters()[j].y + teamRect[i].y);

                float distance = Math::distance(center, point);
                if (distance < minDistance) {
                    position.color = colorRecognizer[k].getColor();
                    position.points = colorRecognizer[k].getCenters();
                    minDistance = distance;
                }
            }
        }


        for (unsigned int j = 0; j < position.points.size(); j++) {
            position.points[j].x += teamRect[i].x;
            position.points[j].y += teamRect[i].y;
            playerColorPosition.push_back(position);
        }

        if (position.points.empty()) {
            playerColorPosition.push_back(position);
        }

    }
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