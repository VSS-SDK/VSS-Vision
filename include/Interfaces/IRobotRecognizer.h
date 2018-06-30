//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_IROBOTRECOGNIZER_H
#define VSS_VISION_IROBOTRECOGNIZER_H

#include <vector>
#include "Domain/Ball.h"
#include <Domain/Robot.h>
#include <Domain/ObjectType.h>
#include <map>
#include "ColorPosition.h"

class IRobotRecognizer {

public:

    virtual std::vector<vss::Robot> recognizeTeam(std::vector< std::vector<ColorPosition>>&, ColorType) = 0;
    virtual std::vector<vss::Robot> recognizeOpponent(std::vector< std::vector<ColorPosition>>&, ColorType) = 0;
    virtual vss::Ball recognizeBall(ColorPosition&) = 0;

    virtual std::vector<vss::Robot> getBlueRobots() = 0;
    virtual std::vector<vss::Robot> getYellowRobots() = 0;
    virtual vss::Ball getBall() = 0;
};

#endif

