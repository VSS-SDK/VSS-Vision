/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef VSS_VISION_PATTERNRECOGNIZER_H
#define VSS_VISION_PATTERNRECOGNIZER_H

#include <Domain/ObjectType.h>
#include <Domain/Calibration.h>
#include <Domain/ColorPattern.h>
#include <Helpers/TimeHelper.h>
#include <Helpers/FrameHelper.h>
#include <Interfaces/IColorRecognizer.h>
#include <Interfaces/IPatternRecognizer.h>

class PatternRecognizer : public IPatternRecognizer{

public:
    PatternRecognizer(Calibration, std::vector<ColorPattern>);

private:

    void recognizeMainColor(cv::Mat, IColorRecognizer*, ObjectType);
    void recognizeSecondColor(cv::Mat);
    void recognizePattern(cv::Mat);

    IColorRecognizer *ballColorRecognizer;
    IColorRecognizer *teamColorRecognizer;
    IColorRecognizer *opponentColorRecognizer;
    IColorRecognizer *colorRecognizer1;
    IColorRecognizer *colorRecognizer2;

    Calibration calibration;
    TimeHelper timeOptimization;
    std::vector<ColorPattern> pattern;

};

#endif //VSS_VISION_PATTERNRECOGNIZER_H
