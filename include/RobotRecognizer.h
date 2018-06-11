//
// Created by manoel on 14/05/18/.
//

#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"
#include "Domain/Ball.h"
#include "Domain/Robot.h"

class RobotRecognizer : public IRobotRecognizer {
	
public:

    RobotRecognizer();
    void recognizeRobots(std::map<WhoseName,ColorPosition>) override;

    std::vector<vss::Robot> getBlueRobots() override;
    std::vector<vss::Robot> getYellowRobots() override;

    vss::Ball getBall() override;

private:

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    std::map<WhoseName, vss::Robot> lastRobotsPos;

    vss::Ball ball;
    vss::Ball lastBallPos;

    double rate;
    double maxDistance;

    void recognizeTeam(std::map<WhoseName,ColorPosition>&);
    void recognizeOpponent(std::map<WhoseName,ColorPosition>&);
    void recognizeBall(std::map<WhoseName,ColorPosition>&);

    vss::Robot calculateRobotsValues(cv::Point teamPos, cv::Point robotPos, WhoseName robotNumber);
};

#endif
