//
// Created by johnathan on 27/02/18.
//

#ifndef VSS_VISION_ICALIBRATIONBUILDER_H
#define VSS_VISION_ICALIBRATIONBUILDER_H

#include <Domain/Calibration.h>

class ICalibrationBuilder{
public:
    virtual void shouldInitializeColors(bool) = 0;
    virtual void shouldInitializeCuts(bool) = 0;

    virtual Calibration getInstance() = 0;
};

#endif //VSS_VISION_ICALIBRATIONBUILDER_H
