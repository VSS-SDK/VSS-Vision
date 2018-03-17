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

    bool getHaveToInitializeColors();
    bool getHaveToInitializeCuts();

    std::vector<ColorRange> getColorsRange();
    std::vector<Point2d> getCuts();

private:
    bool haveToInitializeColors;
    bool haveToInitializeCuts;
};

#endif //VSS_VISION_CALIBRATIONBUILDER_H
