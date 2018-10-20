//
// Created by paulo on 19/10/18.
//

#ifndef VSS_VISION_BALLKALMANFILTER_H
#define VSS_VISION_BALLKALMANFILTER_H

#include "IBallKalmanFilter.h"

class BallKalmanFilter : public IBallKalmanFilter {

public:
    BallKalmanFilter();

    void setBall(vss::Ball) override;
    void setDeltaTime (double) override;
    void setFoundFlag(bool) override;
    vss::Ball getBall() override;
    void init() override;

    void predict() override;
    void update() override;

private:
    cv::KalmanFilter kalmanFilter;
    vss::Ball ballMesured;
    vss::Ball ballPredicted;
    double deltaTime;
    bool foundFlag;
    bool foundDelayFlag;
    int notFoundCount;
    int maxNotFoundCount;

    cv::Mat state;
    cv::Mat measure;
};

#endif //VSS_VISION_BALLKALMANFILTER_H
