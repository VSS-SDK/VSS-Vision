//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_IROBOTRECOGNIZER_H
#define VSS_VISION_IROBOTRECOGNIZER_H

#include <vector>
#include <Robot.h>
#include <Domain/WhoseName.h>
#include <map>
#include "ColorPosition.h"

class IRobotRecognizer {
	
    virtual void recognizeRobots(std::map<WhoseName,ColorPosition>) = 0;
    virtual std::vector<vss::Robot> getRobots() = 0;

};

#endif

