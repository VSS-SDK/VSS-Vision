//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_IROBOTRECOGNIZER_H
#define VSS_VISION_IROBOTRECOGNIZER_H

#include <vector>
#include "Domain/Ball.h"
#include <Domain/Robot.h>
#include <Domain/WhoseName.h>
#include <map>
#include "ColorPosition.h"

class IRobotRecognizer {

public:
    virtual void recognizeRobots(std::map<WhoseName,ColorPosition>) = 0;
    virtual std::vector<vss::Robot> getRobots() = 0;
    virtual vss::Ball getBall() = 0;
};

#endif

