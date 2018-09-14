#ifndef VSS_VISION_ROBOTRECOGNIZER_H
#define VSS_VISION_ROBOTRECOGNIZER_H

#include "Interfaces/IRobotRecognizer.h"
#include "Domain/Ball.h"
#include "Domain/Robot.h"
#include "Domain/ColorSide.h"

class RobotRecognizer : public IRobotRecognizer {

public:

    RobotRecognizer();
    void recognizeRobots(std::map<ObjectType,ColorPosition>) override;

    std::vector<vss::Robot> getBlueRobots() override;
    std::vector<vss::Robot> getYellowRobots() override;

    vss::Ball getBall() override;

private:

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    vss::Ball ball;
    vss::Ball lastBallPos;

    void recognizeTeam(ColorPosition, std::vector<ColorPosition>);
    void recognizeOpponent(ColorPosition);
    void recognizeBall(ColorPosition);

    ColorSide recognizeSide(double farthestAngle, double closestAngle);


    vss::Robot calculateRobotsValues(cv::Point2f teamPos, cv::Point2f robotPos, ObjectType robotNumber);
};

#endif
