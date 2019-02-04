//
// Created by paulo on 19/10/18.
//

#ifndef VSS_VISION_IBALLKALMANFILTER_H
#define VSS_VISION_IBALLKALMANFILTER_H

#include "Domain/Ball.h"
#include <opencv2/core/core.hpp>
#include "opencv2/video/tracking.hpp"


class IBallKalmanFilter {

public:
    virtual void setBall(vss::Ball) = 0;
    virtual void setDeltaTime (double) = 0;
    virtual void setFoundFlag(bool) = 0;
    virtual vss::Ball getBall() = 0;
    virtual void init() = 0;

    virtual void predict() = 0;
    virtual void update() = 0;

};

#endif //VSS_VISION_IBALLKALMANFILTER_H
