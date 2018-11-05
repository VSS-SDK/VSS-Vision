/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VSS_VISION_PATTERNRECOGNIZER_H
#define VSS_VISION_PATTERNRECOGNIZER_H

#include <ColorRecognizer.h>
#include <Domain/ObjectType.h>
#include <Domain/Calibration.h>
#include <Domain/ColorPattern.h>
#include <Domain/ColorPosition.h>
#include <Helpers/TimeHelper.h>
#include <Helpers/FrameHelper.h>
#include <Helpers/Math.h>
#include <Interfaces/IColorRecognizer.h>
#include <Interfaces/IPatternRecognizer.h>
#include <vector>

class PatternRecognizer : public IPatternRecognizer{

public:
    PatternRecognizer();

    void recognizeMainColorBall(cv::Mat) override;
    void recognizeMainColorTeam(cv::Mat) override;
    void recognizeMainColorOpponent(cv::Mat) override;
    void recognizeSecondColor(cv::Mat) override;
    void setRangeVector(std::vector<ColorRange>) override;
    void setPatternVector(std::vector<ColorPattern>) override;


    ColorPosition getBallMainColorPosition() override;
    ColorPosition getTeamMainColorPosition() override;
    ColorPosition getOpponentMainColorPosition() override;
    std::vector<ColorPosition> getTeamSecondColorPosition() override;

    std::vector<cv::RotatedRect> getBallRotatedRect() override;
    std::vector<cv::RotatedRect> getTeamRotatedRect() override;
    std::vector<cv::RotatedRect> getOpponentRotatedRect() override;

    cv::Mat getImage() override;
    std::vector<cv::Rect> getRect() override;
    std::vector<cv::RotatedRect> getRotatedRect() override;

private:
    IColorRecognizer *ballColorRecognizer;
    IColorRecognizer *teamColorRecognizer;
    IColorRecognizer *opponentColorRecognizer;
    IColorRecognizer *colorRecognizer1;
    IColorRecognizer *colorRecognizer2;
    IColorRecognizer *colorRecognizer3;

    TimeHelper timeBall;
    TimeHelper timeTeam;
    TimeHelper timeOpponent;

    std::vector<ColorRange> range;
    std::vector<ColorPattern> pattern;
    std::vector<ColorPosition> playerColorPosition;

    cv::Mat testImage;
    std::vector<cv::Rect> testRect;
    std::vector<cv::RotatedRect> testRotatedRect;
};

#endif //VSS_VISION_PATTERNRECOGNIZER_H
