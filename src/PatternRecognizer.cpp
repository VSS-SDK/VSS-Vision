/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "PatternRecognizer.h"

PatternRecognizer::PatternRecognizer(Calibration c, std::vector<ColorPattern> p) {
    pattern = p;
    calibration = c;
}

void PatternRecognizer::recognizePattern(cv::Mat image) {
    recognizeMainColor(image, ballColorRecognizer, ObjectType::Ball);
    recognizeMainColor(image, teamColorRecognizer, ObjectType::Team);
    recognizeMainColor(image, opponentColorRecognizer, ObjectType::Opponent);

    recognizeSecondColor(image);

    robotRecognizer->
}

void PatternRecognizer::recognizeMainColor(cv::Mat image, IColorRecognizer *recognizer, ObjectType type) {
    ColorPattern findPattern = pattern[type];

    if (findPattern.id == type) {
        recognizer->setColorRange(findPattern.singleColorRange);

        if (timeOptimization.timeOut(1000)) {
            recognizer->processImage(image);
        } else {
            recognizer->processImageInSector(image, recognizer->getRectangles());
        }
    }

}

void PatternRecognizer::recognizeSecondColor(cv::Mat image) {
    std::vector<cv::Rect> rect = teamColorRecognizer->getRectangles();
    std::vector<cv::RotatedRect> rotatedRect = teamColorRecognizer->getRotatedRectangles();

    for (unsigned int i = 0; i < rect.size(); i++) {

        cv::Mat cuttedImage = cropImage(image, rect[i], 0.3);
        rotatedRect[i] = increaseRotatedRect(rotatedRect[i], 1.8, 1.2);

        ColorRange colorRange1 (calibration.colorsRange, ColorType::Green);
        colorRecognizer1->setColorRange(colorRange1);
        colorRecognizer1->processImage(cuttedImage);
        colorRecognizer1->deleteOutsidePoint(rotatedRect[i], rect[i]);

        ColorRange colorRange2 (calibration.colorsRange, ColorType::Pink);
        colorRecognizer2->setColorRange(colorRange2);
        colorRecognizer2->processImage(cuttedImage);
        colorRecognizer2->deleteOutsidePoint(rotatedRect[i], rect[i]);
    }
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