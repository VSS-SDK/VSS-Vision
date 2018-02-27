//
// Created by johnathan on 27/02/18.
//

#ifndef VSS_VISION_CALIBRATIONFACTORY_H
#define VSS_VISION_CALIBRATIONFACTORY_H

#include <Domain/Calibration.h>
#include <Interfaces/ICalibrationFactory.h>

class CalibrationFactory : public ICalibrationFactory{
public:
    Calibration createCalibrationWithoutColors();
    Calibration createCalibrationWithoutCuts();
    Calibration createCalibrationWithoutColorsAndCuts();
    Calibration createCalibrationWithColorsAndCuts();
};

#endif //VSS_VISION_CALIBRATIONFACTORY_H
