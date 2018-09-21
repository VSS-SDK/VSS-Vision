/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

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
    virtual std::vector<vss::Robot> getBlueRobots() = 0;
    virtual std::vector<vss::Robot> getYellowRobots() = 0;
    virtual vss::Ball getBall() = 0;
};

#endif

