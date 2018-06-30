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

    std::vector<vss::Robot> recognizeTeam(std::vector< std::vector<ColorPosition>>&, ColorType) override;
    std::vector<vss::Robot> recognizeOpponent(ColorPosition&, ColorType) override;
    vss::Ball recognizeBall(ColorPosition&) override;

    std::vector<vss::Robot> getBlueRobots() override;
    std::vector<vss::Robot> getYellowRobots() override;

    vss::Ball getBall() override;

private:

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    std::vector<vss::Robot> lastRobotsPos;

    vss::Ball ball;
    vss::Ball lastBallPos;

    double rate;

    vss::Robot buildOpponent(cv::Point2f&);

    vss::Robot buildRobot1(cv::Point2f&, std::vector<cv::Point2f>&, std::vector<cv::Point2f>&);
    vss::Robot buildRobot2(cv::Point2f&, std::vector<cv::Point2f>&, std::vector<cv::Point2f>&);
    vss::Robot buildRobot3(cv::Point2f&, std::vector<cv::Point2f>&, std::vector<cv::Point2f>&);

    float calculateAngle(cv::Point2f, cv::Point2f);

    vss::Robot calculateRobotsValues(cv::Point2f teamPos, cv::Point2f robotPos, ObjectType robotNumber);
};

#endif
