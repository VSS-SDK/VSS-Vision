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
    teamColorRecognizer = new ColorRecognizer;
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

void PatternRecognizer::recognizeMainColor(cv::Mat image, ObjectType type) {
    
    if (type == ObjectType::Ball) {
        if (pattern[type].id == type) {
            ballColorRecognizer->setColorRange(pattern[type].singleColorRange);
            
            if (timeOptimization.timeOut(100)) { 
                ballColorRecognizer->processImage(image); 
            } else { 
                ballColorRecognizer->processImageInSector(image, ballColorRecognizer->getRectangles()); 
            }
        }
    }

    if (type == ObjectType::Team) {;
        if (pattern[type].id == type) {
            teamColorRecognizer->setColorRange(pattern[type].singleColorRange);
            
            if (timeOptimization.timeOut(100)) { 
                teamColorRecognizer->processImage(image); 
            } else { 
                teamColorRecognizer->processImageInSector(image, teamColorRecognizer->getRectangles()); 
            }
        }
    }

    if (type == ObjectType::Opponent) {
        if (pattern[type].id == type) {
            opponentColorRecognizer->setColorRange(pattern[type].singleColorRange);
            
            if (timeOptimization.timeOut(100)) { 
                opponentColorRecognizer->processImage(image); 
            } else { 
                opponentColorRecognizer->processImageInSector(image, opponentColorRecognizer->getRectangles()); 
            }
        }
    }

    
}

void PatternRecognizer::recognizeSecondColor(cv::Mat image) {
    std::vector<cv::Rect> rect = teamColorRecognizer->getRectangles();
    std::vector<cv::RotatedRect> rotatedRect = teamColorRecognizer->getRotatedRectangles();

    playerColorPosition.clear();

    for (unsigned int i = 0; i < rect.size(); i++) {
        cv::Mat cuttedImage = cropImage(image, rect[i], 0.3);
        rotatedRect[i] = increaseRotatedRect(rotatedRect[i], 1.8, 1.2);

        ColorRange colorRange1 (range, ColorType::Green);
        colorRecognizer1->setColorRange(colorRange1);
        colorRecognizer1->processImage(cuttedImage);
        colorRecognizer1->deleteOutsidePoint(rotatedRect[i], rect[i]);

        ColorRange colorRange2 (range, ColorType::Pink);
        colorRecognizer2->setColorRange(colorRange2);
        colorRecognizer2->processImage(cuttedImage);
        colorRecognizer2->deleteOutsidePoint(rotatedRect[i], rect[i]);

        if (colorRecognizer1->getCenters().size() > 0) {
            ColorPosition position;
            position.color = colorRecognizer1->getColor();
            position.points = colorRecognizer1->getCenters();
            playerColorPosition.push_back (position);
        }

        if (colorRecognizer2->getCenters().size() > 0){
            ColorPosition position;
            position.color = colorRecognizer2->getColor();
            position.points = colorRecognizer2->getCenters();
            playerColorPosition.push_back(position);
        }
    }
}

std::vector<ColorPosition> PatternRecognizer::getPlayerColorPosition() {
        return playerColorPosition;
}

ColorPosition PatternRecognizer::getBallColorPosition() {
    ColorPosition position;
    position.color = ballColorRecognizer->getColor();
    position.points = ballColorRecognizer->getCenters();
    return position;
}

ColorPosition PatternRecognizer::getTeamColorPosition() {
    ColorPosition position;
    position.color = teamColorRecognizer->getColor();
    position.points = teamColorRecognizer->getCenters();
    return position;
}

ColorPosition PatternRecognizer::getOpponnetColorPosition() {
    ColorPosition position;
    position.color = opponentColorRecognizer->getColor();
    position.points = opponentColorRecognizer->getCenters();
    return position;
}

/*
    // DRAW RECTANGLES
    for (unsigned int j = 0; j < colorRecognizer2->getRotatedRectangles().size(); j++) {
        cv::RotatedRect r = colorRecognizer2->getRotatedRectangles()[j];
        r.center.x += rect[i].x;
        r.center.y += rect[i].y;

        drawRotatedRectangle(image, r);
    }

    for (unsigned int j = 0; j < colorRecognizer1->getRotatedRectangles().size(); j++) {
        cv::RotatedRect r = colorRecognizer1->getRotatedRectangles()[j];
            r.center.x += rect[i].x;
            r.center.y += rect[i].y;

        drawRotatedRectangle(image, r);
    }
    frame = drawRectangle(image, rect);
*/