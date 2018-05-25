//
// Created by manoel on 21/05/18.
//

#include <Helpers/Math.h>
#include <Ball.h>
#include "RobotRecognizer.h"

RobotRecognizer::RobotRecognizer() {
    vss::Robot initialRobot;
    initialRobot.x = initialRobot.y = 0;
    initialRobot.speedX = initialRobot.speedY = 0;
    initialRobot.speedAngle = 0;

    ball.x = ball.y = 0;
    ball.speedX = ball.speedY = 0;

    lastRobotsPos.insert(std::make_pair(WhoseName::Robot1, initialRobot));
    lastRobotsPos.insert(std::make_pair(WhoseName::Robot2, initialRobot));
    lastRobotsPos.insert(std::make_pair(WhoseName::Robot3, initialRobot));
    lastRobotsPos.insert(std::make_pair(WhoseName::Robot4, initialRobot));
    lastRobotsPos.insert(std::make_pair(WhoseName::Robot5, initialRobot));

    lastBallPos = ball;

    // 1/60
    rate = 0.016;
    // max distance between colors to be considered a robot
    maxDistance = 30;
}

void RobotRecognizer::recognizeRobots(std::map<WhoseName, ColorPosition> colorsPos) {

    std::vector<vss::Robot> blueRobots;
    std::vector<vss::Robot> yellowRobots;

    if(not colorsPos.empty()) {

        // iterate through team1 and team2
        for (int teamInt = WhoseName::Team1; teamInt != WhoseName::Robot1; teamInt++) {

            auto teamNumber = static_cast<WhoseName>(teamInt);

            auto &teamPositions = colorsPos[teamNumber].points;
            auto &teamColor = colorsPos[teamNumber].color;

            if (teamColor == ColorType::UnknownType or teamPositions.empty()) continue;

            // iterate through robots
            for (int robotInt = WhoseName::Robot1; robotInt <= WhoseName::Robot5; robotInt++) {

                auto robotNumber = static_cast<WhoseName>(robotInt);

                auto &robotPositions = colorsPos[robotNumber].points;
                auto &robotColor = colorsPos[robotNumber].color;

                if (robotColor == ColorType::UnknownType or robotPositions.empty()) continue;

                auto itRobotPos = robotPositions.end();
                auto itTeamPos = teamPositions.end();

                double minDistance = 10000;

                // searches for a robot point which matches with team point
                for (unsigned int i = 0; i < robotPositions.size(); i++) {
                    for (unsigned int j = 0; j < teamPositions.size(); j++) {

                        double distance = Math::distance(robotPositions.at(i), teamPositions.at(j));

                        if (distance < minDistance and distance < maxDistance) {
                            minDistance = distance;
                            itRobotPos = robotPositions.begin() + i;
                            itTeamPos = teamPositions.begin() + j;
                        }
                    }
                }

                // with the closer point found update robot's values
                vss::Robot robot;
                if (itRobotPos != robotPositions.end() and itTeamPos != teamPositions.end()) {
                    auto midPoint = Math::midPoint(*itRobotPos, *itTeamPos);

                    robot.x = midPoint.x;
                    robot.y = midPoint.y;
                    //@TODO verificar angulacao
                    robot.angle = atan2(itRobotPos->y - itTeamPos->y, itRobotPos->x - itTeamPos->x) * (180 / CV_PI);

                    robot.speedAngle = (robot.angle - lastRobotsPos[robotNumber].angle) / rate;
                    robot.speedX = (robot.x - lastRobotsPos[robotNumber].x) / rate;
                    robot.speedY = (robot.y - lastRobotsPos[robotNumber].y) / rate;

                    // removes used points to optimize searching
                    teamPositions.erase(itTeamPos);
                    robotPositions.erase(itRobotPos);

                    lastRobotsPos[robotNumber] = robot;

                    if (teamColor == ColorType::Yellow)
                        yellowRobots.push_back(robot);
                    else
                        blueRobots.push_back(robot);
                }
            }
        }

        // calculates ball values
        if(not colorsPos[WhoseName::Ball].points.empty()) {
            ball.x = colorsPos[WhoseName::Ball].points.front().x;
            ball.y = colorsPos[WhoseName::Ball].points.front().y;

            ball.speedX = (ball.x - lastBallPos.x) / rate;
            ball.speedY = (ball.y - lastBallPos.y) / rate;

            lastBallPos = ball;
        }
    }

    // concatenate blue vector and yellow vector
    vss::Robot nullRobot;
    nullRobot.x = nullRobot.y = 0;
    nullRobot.angle = nullRobot.speedAngle = 0;
    nullRobot.speedX = nullRobot.speedY = 0;

    // fill each vector with 3 positions
    blueRobots.resize(3, nullRobot);
    yellowRobots.resize(3, nullRobot);

    // yellow robots in the beginning
    robots.clear();
    robots.insert(robots.begin(), yellowRobots.begin(), yellowRobots.end());
    robots.insert(robots.end(), blueRobots.begin(), blueRobots.end());
}

std::vector<vss::Robot> RobotRecognizer::getRobots() {
    return robots;
}

vss::Ball RobotRecognizer::getBall(){
    return ball;
}
