#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"
#include "Domain/Ball.h"
#include "Domain/Robot.h"
#include "Domain/ColorSide.h"
#include "Domain/ColorPosition.h"
#include "Domain/ColorPattern.h"

class RobotRecognizer : public IRobotRecognizer {

public:

    RobotRecognizer();

    void recognizeTeam(ColorPosition, std::vector<ColorPosition>, std::vector<ColorPattern>) override;
    void recognizeOpponent(ColorPosition) override;
    void recognizeBall(ColorPosition) override;

    vss::Ball getBall() override;
    std::vector<vss::Robot> getBlueRobots() override;
    std::vector<vss::Robot> getYellowRobots() override;

private:

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    std::map<ObjectType, vss::Robot> lastRobotsPos;

    vss::Ball ball;
    vss::Ball lastBallPos;

    double rate;

    ColorSide recognizeSide(double farthestAngle, double closestAngle);

    void calculateBallSpeed();
    vss::Robot calculateRobotSpeedsAndFilter(ObjectType id, vss::Robot robot);
    double filter(double current, double last);

};

#endif
