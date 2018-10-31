/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Helpers/Math.h>
#include <Domain/ColorPattern.h>
#include "RobotRecognizer.h"

RobotRecognizer::RobotRecognizer() {
    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());

    lastBlueRobots.resize(5, vss::Robot());
    lastYellowRobots.resize(5, vss::Robot());

    init = true;

    // 1/60
    rate = 0.0105;

    for (int i = 0; i < 5; i++) {
        RobotOpponentKalmanFilter robotTeamKalmanFilter;
        robotTeamKalmanFilter.setDeltaTime(rate);
        robotsTeamKalmanFilter.push_back(robotTeamKalmanFilter);
    }

    for (int i = 0; i < 5; i++) {
        RobotOpponentKalmanFilter robotOpponentKalmanFilter;
        robotOpponentKalmanFilter.setDeltaTime(rate);
        robotsOpponentKalmanFilter.push_back(robotOpponentKalmanFilter);
    }


    ballKalmanFilter.setDeltaTime(rate);
}

void RobotRecognizer::recognizeTeam(ColorPosition teamColor, std::vector<ColorPosition> playerColor,
                                    std::vector<ColorPattern> pattern) {

    for (unsigned int i = 0; i < playerColor.size(); i++){

        if (playerColor[i].points.size() == 3) {

            double dist01 = Math::distance(playerColor[i].points[0], playerColor[i].points[1]);
            double dist02 = Math::distance(playerColor[i].points[0], playerColor[i].points[2]);
            double dist12 = Math::distance(playerColor[i].points[1], playerColor[i].points[2]);

            unsigned int singleColorIndex = 0;
            unsigned int closestColorIndex = 0;
            unsigned int farthestColorIndex = 0;

            if (dist01 < dist02 && dist01 < dist12) {
                singleColorIndex = 2;

                if (dist02 < dist12) {
                    closestColorIndex = 0;
                    farthestColorIndex = 1;
                } else {
                    closestColorIndex = 1;
                    farthestColorIndex = 0;
                }

            } else if (dist02 < dist01 && dist02 < dist12) {
                singleColorIndex = 1;

                if (dist01 < dist12) {
                    closestColorIndex = 0;
                    farthestColorIndex = 2;
                } else {
                    closestColorIndex = 2;
                    farthestColorIndex = 0;
                }

            } else if (dist12 < dist01 && dist12 < dist02) {
                singleColorIndex = 0;

                if (dist01 < dist02) {
                    closestColorIndex = 1;
                    farthestColorIndex = 2;

                } else {
                    closestColorIndex = 2;
                    farthestColorIndex = 1;
                }
            }

            double closestAngle = Math::angle(playerColor[i].points[singleColorIndex],
                                              playerColor[i].points[closestColorIndex]);
            double farthestAngle = Math::angle(playerColor[i].points[singleColorIndex],
                                               playerColor[i].points[farthestColorIndex]);

            ColorSide colorSide = recognizeSide(farthestAngle, closestAngle);

            ColorPattern colorPattern;
            colorPattern.colorSide = colorSide;
            colorPattern.singleColorType = playerColor[i].color;
            colorPattern.doubleColorType = playerColor[i].color;

            vss::Robot robot;
            robot.x = teamColor.points[i].x;
            robot.y = teamColor.points[i].y;

            if (colorSide == ColorSide::Right)
                robot.angle = Math::constrainAngle(farthestAngle + 45);

            if (colorSide == ColorSide::Left)
                robot.angle = Math::constrainAngle(farthestAngle - 45);

            robot = convertRobotPosePixelToCentimeter(robot);


            for (unsigned int j = 3; j < pattern.size() - 1; j++) {

                if (pattern[j].isEquals(colorPattern)) {
                    if (teamColor.color == ColorType::Blue) {
                        blueRobots[j - 3] = robot;
                    } else if (teamColor.color == ColorType::Yellow) {
                        yellowRobots[j - 3] = robot;
                    }
                }
            }

            if (teamColor.color == ColorType::Blue) {
                for (unsigned int i = 0; i < blueRobots.size(); i++) {
                    blueRobots[i] = calculateRobotSpeedsAndFilter(i, blueRobots[i]);
                }
            } else if (teamColor.color == ColorType::Yellow) {
                for (unsigned int i = 0; i < yellowRobots.size(); i++) {
                    yellowRobots[i] = calculateRobotSpeedsAndFilter(i, yellowRobots[i]);
                }
            }
        }
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());
}

void RobotRecognizer::recognizeOpponent(ColorPosition colors) {

    if(colors.points.size() > 5){
        colors.points.resize(5, cv::Point2f());
    }

    if (colors.color == ColorType::Blue) {
        blueRobots.clear();
    } else if (colors.color == ColorType::Yellow) {
        yellowRobots.clear();
    }

    for (unsigned int i = 0; i < colors.points.size(); i++) {
        vss::Robot robot;
        robot.x = colors.points[i].x;
        robot.y = colors.points[i].y;

        robot = convertRobotPosePixelToCentimeter(robot);

        if (colors.color == ColorType::Blue) {
            blueRobots.push_back(robot);
        } else if (colors.color == ColorType::Yellow) {
            yellowRobots.push_back(robot);
        }
    }

    if (init) {
        if (colors.color == ColorType::Blue) {
            lastBlueRobots = blueRobots;
        } else if (colors.color == ColorType::Yellow) {
            lastYellowRobots = yellowRobots;
        }
        init = false;
    }

    keepOpponentOrder(colors.color);

    if (colors.color == ColorType::Blue) {
        for(unsigned int i = 0; i < blueRobots.size(); i++){

            robotsOpponentKalmanFilter[i].setFoundFlag(true);
            robotsOpponentKalmanFilter[i].setRobot(blueRobots[i]);
            robotsOpponentKalmanFilter[i].predict();
            robotsOpponentKalmanFilter[i].update();
            blueRobots[i] = robotsOpponentKalmanFilter[i].getRobot();

        }

        lastBlueRobots = blueRobots;

    } else if (colors.color == ColorType::Yellow) {

        for(unsigned int i = 0; i < yellowRobots.size(); i++){

            robotsOpponentKalmanFilter[i].setFoundFlag(true);
            robotsOpponentKalmanFilter[i].setRobot(yellowRobots[i]);
            robotsOpponentKalmanFilter[i].predict();
            robotsOpponentKalmanFilter[i].update();
            yellowRobots[i] = robotsOpponentKalmanFilter[i].getRobot();

        }

        lastYellowRobots = yellowRobots;
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());
    lastBlueRobots.resize(5, vss::Robot());
    lastYellowRobots.resize(5, vss::Robot());
}

void RobotRecognizer::keepOpponentOrder(ColorType color) {
    std::vector<vss::Robot> robots;
    robots.resize(5, vss::Robot());

    if (color == ColorType::Blue) {

        robots = blueRobots;

        for (unsigned int i = 0; i < blueRobots.size(); i++) {

            if (blueRobots[i].x != 0 && blueRobots[i].y != 0) {

                cv::Point currentRobot(blueRobots[i].x, blueRobots[i].y);
                cv::Point lastRobot;

                double distance = image.cols;
                int id = 0; // Zero is null

                if (lastBlueRobots.size() > 0) {
                    for (unsigned int j = 0; j < lastBlueRobots.size(); j++) {
                        lastRobot.x = lastBlueRobots[j].x;
                        lastRobot.y = lastBlueRobots[j].y;

                        //Find the closest last point from the current, the last must be different from 0,0
                        if (lastRobot.x != 0 && lastRobot.y != 0) {
                            if (Math::distance(currentRobot, lastRobot) < distance) {
                                distance = Math::distance(currentRobot, lastRobot);
                                id = j + 1;
                            }
                        }
                    }

                    if (id > 0) { //If different from null
                        robots[id - 1] = blueRobots[i];
                    }
                }

            }
        }

        blueRobots = robots;

    } else if (color == ColorType::Yellow) {

        robots = yellowRobots;

        for (unsigned int i = 0; i < yellowRobots.size(); i++) {
            if (yellowRobots[i].x != 0 && yellowRobots[i].y != 0) {

                cv::Point currentRobot(yellowRobots[i].x, yellowRobots[i].y);
                cv::Point lastRobot;

                double distance = image.cols;
                int id = 0; //Zero is null

                if (lastYellowRobots.size() > 0) {
                    for (unsigned int j = 0; j < lastYellowRobots.size(); j++) {
                        lastRobot.x = lastYellowRobots[j].x;
                        lastRobot.y = lastYellowRobots[j].y;

                        //Find the closest last point from the current, the last must be different from 0,0
                        if (lastRobot.x != 0 && lastRobot.y != 0) {
                            if (Math::distance(currentRobot, lastRobot) < distance) {
                                distance = Math::distance(currentRobot, lastRobot);
                                id = j + 1;

                            }
                        }
                    }

                    if (id > 0) { //If different of null
                        robots[id - 1] = yellowRobots[i];
                    }
                }

            }
        }

        yellowRobots = robots;
    }
}

void RobotRecognizer::recognizeBall(ColorPosition colors) {
    if (!colors.points.empty()) {
        ball.x = colors.points[0].x;
        ball.y = colors.points[0].y;
    }
    convertBallPosePixelToCentimeter();

    if (ball.x <= 0.1 && ball.y <= 0.1 && ball.y <= -0.1 && ball.x <= -0.1) {
        ballKalmanFilter.setFoundFlag(false);
    } else {
        ballKalmanFilter.setFoundFlag(true);
    }

    ballKalmanFilter.setBall(ball);
    ballKalmanFilter.predict();
    ballKalmanFilter.update();
    ball = ballKalmanFilter.getBall();

}

vss::Robot RobotRecognizer::calculateRobotSpeedsAndFilter(unsigned int id, vss::Robot robot) {

    robotsTeamKalmanFilter[id].setFoundFlag(true);
    robotsTeamKalmanFilter[id].setRobot(robot);
    robotsTeamKalmanFilter[id].predict();
    robotsTeamKalmanFilter[id].update();
    robot = robotsTeamKalmanFilter[id].getRobot();

    return robot;
}

ColorSide RobotRecognizer::recognizeSide(double farthestAngle, double closestAngle) {

    ColorSide colorSide;

    if (abs(closestAngle - farthestAngle) > 90) {
        if (closestAngle > farthestAngle) {
            colorSide = ColorSide::Right;

        } else {
            colorSide = ColorSide::Left;
        }

    } else {
        if (closestAngle > farthestAngle) {
            colorSide = ColorSide::Left;

        } else {
            colorSide = ColorSide::Right;
        }
    }
    return colorSide;
}

vss::Robot RobotRecognizer::convertRobotPosePixelToCentimeter(vss::Robot robot) {
    robot.x = (robot.x * 170) / image.cols;
    robot.y = (robot.y * 130) / image.rows;
    return robot;
}

void RobotRecognizer::convertBallPosePixelToCentimeter() {
    ball.x = (ball.x * 170) / image.cols;
    ball.y = (ball.y * 130) / image.rows;
}

void RobotRecognizer::setImage(cv::Mat image) {
    this->image = image;
}

std::vector<vss::Robot> RobotRecognizer::getBlueRobots() {
    return blueRobots;
}

std::vector<vss::Robot> RobotRecognizer::getYellowRobots() {
    return yellowRobots;
}

vss::Ball RobotRecognizer::getBall() {
    return ball;
}