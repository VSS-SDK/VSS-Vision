//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"

class RobotRecognizer : public IRobotRecognizer {
	
public:

    RobotRecognizer();
    void recognizeRobots(std::map<WhoseName,ColorPosition>) override;
    std::vector<vss::Robot> getRobots() override;
    vss::Ball getBall() override;

private:

    std::vector<vss::Robot> robots;
    std::map<WhoseName, vss::Robot> lastRobotsPos;

    vss::Ball ball;
    vss::Ball lastBallPos;

    double rate;
    double maxDistance;
};

#endif
