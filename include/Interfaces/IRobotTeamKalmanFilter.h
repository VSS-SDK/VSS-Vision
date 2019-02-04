//
// Created by paulo on 19/10/18.
//

#ifndef VSS_VISION_IROBOTTEAMKALMANFILTER_H
#define VSS_VISION_IROBOTTEAMKALMANFILTER_H

#include "Domain/Robot.h"
#include <opencv2/core/core.hpp>
#include "opencv2/video/tracking.hpp"

class IRobotTeamKalmanFilter {

public:
    virtual void setRobot(vss::Robot) = 0;
    virtual void setDeltaTime (double) = 0;
    virtual void setFoundFlag(bool) = 0;
    virtual vss::Robot getRobot() = 0;
    virtual void init() = 0;

    virtual void predict() = 0;
    virtual void update() = 0;

};

#endif //VSS_VISION_IROBOTTEAMKALMANFILTER_H
