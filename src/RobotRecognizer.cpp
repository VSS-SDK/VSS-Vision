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


    vss::Robot initialRobot;
    initialRobot.x = initialRobot.y = 0;
    initialRobot.speedX = initialRobot.speedY = 0;
    initialRobot.speedAngle = 0;

    ball.x = ball.y = 0;
    ball.speedX = ball.speedY = 0;

    init = true;

    for (int i = 0; i < lastsNumber; i++) {
        std::map<ObjectType, vss::Robot> lastRobotsPos;
        lastRobotsPos.insert(std::make_pair(ObjectType::Robot1, initialRobot));
        lastRobotsPos.insert(std::make_pair(ObjectType::Robot2, initialRobot));
        lastRobotsPos.insert(std::make_pair(ObjectType::Robot3, initialRobot));
        lastRobotsPos.insert(std::make_pair(ObjectType::Robot4, initialRobot));
        lastRobotsPos.insert(std::make_pair(ObjectType::Robot5, initialRobot));

        lastsRobotsPos.push_back(lastRobotsPos);
        lastsBallPos.push_back(ball);
    }

    // 1/60
    rate = 0.016;

    RobotTeamKalmanFilter robotTeamKalmanFilter;
    robotTeamKalmanFilter.setDeltaTime(rate);

    robotsTeamKalmanFilter.insert(std::make_pair(ObjectType::Robot1, robotTeamKalmanFilter));
    robotsTeamKalmanFilter.insert(std::make_pair(ObjectType::Robot2, robotTeamKalmanFilter));
    robotsTeamKalmanFilter.insert(std::make_pair(ObjectType::Robot3, robotTeamKalmanFilter));
    robotsTeamKalmanFilter.insert(std::make_pair(ObjectType::Robot4, robotTeamKalmanFilter));
    robotsTeamKalmanFilter.insert(std::make_pair(ObjectType::Robot5, robotTeamKalmanFilter));

    ballKalmanFilter.setDeltaTime(rate);
}

void RobotRecognizer::recognizeTeam(ColorPosition teamColor, std::vector<ColorPosition> playerColor,
                                    std::vector<ColorPattern> pattern) {

    if (not playerColor.empty()) {

        for (unsigned int i = 0; i < teamColor.points.size(); i++) {

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
                robot.angle = Math::constrainAngle(farthestAngle + 45);

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
                        blueRobots[i] = calculateRobotSpeedsAndFilter(static_cast<ObjectType>(i), blueRobots[i]);
                    }
                } else if (teamColor.color == ColorType::Yellow) {
                    for (unsigned int i = 0; i < yellowRobots.size(); i++) {
                        yellowRobots[i] = calculateRobotSpeedsAndFilter(static_cast<ObjectType>(i), yellowRobots[i]);
                    }
                }

            }
        }
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());
}

void RobotRecognizer::recognizeOpponent(ColorPosition colors) {
    if (colors.color == ColorType::Blue) {
        blueRobots.clear();
    } else if (colors.color == ColorType::Yellow) {
        yellowRobots.clear();
    }

    for (unsigned int i = 0; i < colors.points.size(); i++) {
        vss::Robot robot;
        robot.x = colors.points[i].x;
        robot.y = colors.points[i].y;

        if (colors.color == ColorType::Blue) {
            blueRobots.push_back(robot);
        } else if (colors.color == ColorType::Yellow) {
            yellowRobots.push_back(robot);
        }
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());


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
        lastBlueRobots = blueRobots;
    } else if (colors.color == ColorType::Yellow) {
        lastYellowRobots = yellowRobots;
    }
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
                            if (Math::distance(currentRobot, lastRobot) <= distance) {
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
                            if (Math::distance(currentRobot, lastRobot) <= distance) {
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
    //std::cout << ball << std::endl;

    //convertBallPosePixelToCentimeter();
    if (ball.x <= 0.1 && ball.y <= 0.1 && ball.y <= -0.1 && ball.x <= -0.1) {
        ballKalmanFilter.setFoundFlag(false);
        //std::cout<<"sumiu"<<std::endl;
    } else {
        ballKalmanFilter.setFoundFlag(true);
    }

    ballKalmanFilter.setBall(ball);
    ballKalmanFilter.predict();
    ballKalmanFilter.update();
    ball = ballKalmanFilter.getBall();

    //filterBallPosition();
    //calculateBallSpeed();
    //filterBallSpeed();

    std::vector<vss::Ball> lastsBallPosAux = lastsBallPos;
    lastsBallPos[0] = ball;
    for (int i = 1; i < lastsNumber; i++) {
        lastsBallPos[i] = lastsBallPosAux[i - 1];
    }

}

void RobotRecognizer::calculateBallSpeed() {

    ball.speedX = (ball.x - lastsBallPos[0].x) / rate;
    ball.speedY = (ball.y - lastsBallPos[0].y) / rate;

}

void RobotRecognizer::filterBallPosition() {
    double sumX = ball.x;
    double sumY = ball.y;

    for (int i = 0; i < lastsNumber; i++) {
        sumX += lastsBallPos[i].x;
        sumY += lastsBallPos[i].y;
    }

    ball.x = sumX / (lastsNumber + 1);
    ball.y = sumY / (lastsNumber + 1);
}

void RobotRecognizer::filterBallSpeed() {
    double sumXSpeed = ball.speedX;
    double sumYSpeed = ball.speedY;

    for (int i = 0; i < lastsNumber; i++) {
        sumXSpeed += lastsBallPos[i].speedX;
        sumYSpeed += lastsBallPos[i].speedY;
    }

    ball.speedX = int(sumXSpeed / (lastsNumber + 1));
    ball.speedY = int(sumYSpeed / (lastsNumber + 1));
}

vss::Robot RobotRecognizer::calculateRobotSpeedsAndFilter(ObjectType id, vss::Robot robot) {
    /*double sumX = robot.x;
    double sumY = robot.y;
    double sumAngle = robot.angle;

    for(int i = 0;i < lastsNumber; i++){
        sumX += lastsRobotsPos[i][id].x;
        sumY += lastsRobotsPos[i][id].y;
        sumAngle += lastsRobotsPos[i][id].angle;

    }

    robot.x = sumX/(lastsNumber + 1);
    robot.y = sumY/(lastsNumber + 1);
    robot.angle = sumAngle/(lastsNumber + 1);


    robot.speedAngle = (robot.angle - lastsRobotsPos[0][id].angle) / rate;
    robot.speedX = (robot.x - lastsRobotsPos[0][id].x) / rate;
    robot.speedY = (robot.y - lastsRobotsPos[0][id].y) / rate;

    double sumXSpeed = robot.speedX;
    double sumYSpeed = robot.speedY;
    double sumAngleSpeed = robot.speedAngle;

    for(int i = 0;i < lastsNumber; i++){
        sumXSpeed += lastsRobotsPos[i][id].speedX;
        sumYSpeed += lastsRobotsPos[i][id].speedY;
        sumAngleSpeed += lastsRobotsPos[i][id].speedAngle;

    }

    robot.speedX = int (sumXSpeed/(lastsNumber + 1));
    robot.speedY = int (sumYSpeed/(lastsNumber + 1));
    robot.speedAngle = int (sumAngleSpeed/(lastsNumber + 1));

    std::vector<std::map<ObjectType, vss::Robot>> lastsRobotsPosAux = lastsRobotsPos;
    lastsRobotsPos[0][id] = robot;
    for(int i = 1; i < lastsNumber; i++){
        lastsRobotsPos[i][id] = lastsRobotsPosAux[i-1][id];
    }*/
    //if(id == 0){
    //    std::cout<<"Medição do robô: "<<id<<std::endl;
    //    std::cout<<robot<<std::endl;
    //}
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