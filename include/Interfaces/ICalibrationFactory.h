//
// Created by johnathan on 27/02/18.
//

#ifndef VSS_VISION_ICALIBRATIONFACTORY_H
#define VSS_VISION_ICALIBRATIONFACTORY_H

#include <Domain/Calibration.h>

class ICalibrationFactory{
public:
    virtual Calibration createCalibrationWithoutColors() = 0;
    virtual Calibration createCalibrationWithoutCuts() = 0;
    virtual Calibration createCalibrationWithoutColorsAndCuts() = 0;
    virtual Calibration createCalibrationWithColorsAndCuts() = 0;
};

#endif //VSS_VISION_ICALIBRATIONFACTORY_H
