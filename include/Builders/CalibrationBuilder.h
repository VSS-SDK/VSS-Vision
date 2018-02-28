//
// Created by johnathan on 27/02/18.
//

#ifndef VSS_VISION_CALIBRATIONBUILDER_H
#define VSS_VISION_CALIBRATIONBUILDER_H

#include <Domain/Calibration.h>
#include <Interfaces/ICalibrationBuilder.h>

class CalibrationBuilder : public ICalibrationBuilder{
public:
    CalibrationBuilder();

    void shouldInitializeColors(bool) override;
    void shouldInitializeCuts(bool) override;

    Calibration getInstance();

private:
    bool haveToInitializeColors;
    bool haveToInitializeCuts;

    std::vector<ColorRange> getColorsRange();
    std::vector<Point2d> getCuts();
};

#endif //VSS_VISION_CALIBRATIONBUILDER_H
