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

    vss::Robot initialRobot;
    initialRobot.x = initialRobot.y = 0;
    initialRobot.speedX = initialRobot.speedY = 0;
    initialRobot.speedAngle = 0;

    ball.x = ball.y = 0;
    ball.speedX = ball.speedY = 0;

    lastRobotsPos.insert(std::make_pair(ObjectType::Robot1, initialRobot));
    lastRobotsPos.insert(std::make_pair(ObjectType::Robot2, initialRobot));
    lastRobotsPos.insert(std::make_pair(ObjectType::Robot3, initialRobot));
    lastRobotsPos.insert(std::make_pair(ObjectType::Robot4, initialRobot));
    lastRobotsPos.insert(std::make_pair(ObjectType::Robot5, initialRobot));

    lastBallPos = ball;

    // 1/60
    rate = 0.016;
}

void RobotRecognizer::recognizeTeam(ColorPosition teamColor, std::vector<ColorPosition> playerColor, std::vector<ColorPattern> pattern){
    
    if (not playerColor.empty()) {

        for (unsigned int i = 0; i < teamColor.points.size(); i++){
            
            if (playerColor[i].points.size() == 3) {

                double dist01 = Math::distance(playerColor[i].points[0], playerColor[i].points[1]);
                double dist02 = Math::distance(playerColor[i].points[0], playerColor[i].points[2]);
                double dist12 = Math::distance(playerColor[i].points[1], playerColor[i].points[2]);

                unsigned int singleColorIndex = 0;
                unsigned int closestColorIndex = 0;
                unsigned int farthestColorIndex = 0;

                if(dist01 < dist02 && dist01 < dist12){
                    singleColorIndex = 2;

                    if(dist02 < dist12){
                        closestColorIndex = 0;
                        farthestColorIndex = 1;
                    }else{
                        closestColorIndex = 1;
                        farthestColorIndex = 0;
                    }

                } else if(dist02 < dist01 && dist02 < dist12){
                    singleColorIndex = 1;

                    if (dist01 < dist12){
                        closestColorIndex = 0;
                        farthestColorIndex = 2;
                    }else{
                        closestColorIndex = 2;
                        farthestColorIndex = 0;
                    }

                } else if(dist12 < dist01 && dist12 < dist02){
                    singleColorIndex = 0;

                    if(dist01 < dist02){
                        closestColorIndex = 1;
                        farthestColorIndex = 2;

                    }else{
                        closestColorIndex = 2;
                        farthestColorIndex = 1;
                    }
                }

                double closestAngle = Math::angle(playerColor[i].points[singleColorIndex], playerColor[i].points[closestColorIndex]);
                double farthestAngle = Math::angle(playerColor[i].points[singleColorIndex], playerColor[i].points[farthestColorIndex]);

                ColorSide colorSide = recognizeSide(farthestAngle, closestAngle);
                
                ColorPattern colorPattern;
                colorPattern.colorSide = colorSide;
                colorPattern.singleColorType = playerColor[i].color;
                colorPattern.doubleColorType = playerColor[i].color;

                vss::Robot robot;
                robot.x = teamColor.points[i].x;
                robot.y = teamColor.points[i].y;
                robot.angle = farthestAngle;


                for(unsigned int j = 3; j < pattern.size() - 1; j++){

                    if(pattern[j].isEquals(colorPattern)){
                        if(teamColor.color == ColorType::Blue){
                            blueRobots[j-3] = robot;
                        }else if(teamColor.color == ColorType::Yellow){
                            yellowRobots[j-3] = robot;
                        }
                    }
                }

                if(teamColor.color == ColorType::Blue){
                    for(unsigned int i = 0; i < blueRobots.size(); i++){
                        blueRobots[i] = calculateRobotSpeedsAndFilter(static_cast<ObjectType>(i), blueRobots[i]);
                    }
                }else if(teamColor.color == ColorType::Yellow){
                    for(unsigned int i = 0; i < yellowRobots.size(); i++){
                        yellowRobots[i] = calculateRobotSpeedsAndFilter(static_cast<ObjectType>(i), yellowRobots[i]);
                    }
                }

            }
        }
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());
}

void RobotRecognizer::recognizeOpponent(ColorPosition colors){
    
    if(colors.color == ColorType::Blue){       
        blueRobots.clear();
    }else if(colors.color == ColorType::Yellow){
        yellowRobots.clear();
    }

    for(unsigned int i = 0; i < colors.points.size(); i++){
        vss::Robot robot;
        robot.x = colors.points[i].x;
        robot.y = colors.points[i].y;

        if(colors.color == ColorType::Blue){
            blueRobots.push_back(robot);
        }else if(colors.color == ColorType::Yellow){
            yellowRobots.push_back(robot);
        }
    }

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());
}

void RobotRecognizer::recognizeBall(ColorPosition colors){
    if(!colors.points.empty()){
        ball.x = colors.points[0].x;
        ball.y = colors.points[0].y;
    }
    ball.x = filter(ball.x, lastBallPos.x);
    ball.y = filter(ball.y, lastBallPos.y);

    calculateBallSpeed();
    lastBallPos = ball;
    //std::cout<< ball.speedX << " " << ball.speedY << std::endl;
}

void RobotRecognizer::calculateBallSpeed() {

    ball.speedX = (ball.x - lastBallPos.x) / rate;
    ball.speedY = (ball.y - lastBallPos.y) / rate;

    ball.speedX = filter(ball.speedX, lastBallPos.speedX);
    ball.speedY = filter(ball.speedY, lastBallPos.speedY);
}

vss::Robot RobotRecognizer::calculateRobotSpeedsAndFilter(ObjectType id, vss::Robot robot) {
    robot.x = filter(robot.x, lastRobotsPos[id].x);
    robot.y = filter(robot.y, lastRobotsPos[id].y);
    robot.angle = filter(robot.angle, lastRobotsPos[id].angle);

    robot.speedAngle = (robot.angle - lastRobotsPos[id].angle) / rate;
    robot.speedX = (robot.x - lastRobotsPos[id].x) / rate;
    robot.speedY = (robot.y - lastRobotsPos[id].y) / rate;

    robot.speedAngle = filter(robot.speedAngle, lastRobotsPos[id].speedAngle);
    robot.speedX = filter(robot.speedX, lastRobotsPos[id].speedX);
    robot.speedY = filter(robot.speedY, lastRobotsPos[id].speedY);

    lastRobotsPos[id] = robot;

    return robot;
}

ColorSide RobotRecognizer::recognizeSide(double farthestAngle, double closestAngle) {

    ColorSide colorSide;

    if ( abs(closestAngle - farthestAngle) > 90 ) {
        if(closestAngle > farthestAngle){
            colorSide = ColorSide::Right;
        
        } else {
            colorSide = ColorSide ::Left;
        }

    } else {
        if(closestAngle > farthestAngle){
            colorSide = ColorSide::Left;
        
        } else {
            colorSide = ColorSide ::Right;
        }
    }
    return colorSide;
}

double RobotRecognizer::filter(double current, double last) {
    float weight = 0.9;
    //return (last + (1-weight)*(current - last));
    //return (weight*last + (1-weight)*current);
    return (current + last)/2;
}

std::vector<vss::Robot> RobotRecognizer::getBlueRobots(){
    return blueRobots;
}

std::vector<vss::Robot> RobotRecognizer::getYellowRobots(){
    return yellowRobots;
}

vss::Ball RobotRecognizer::getBall(){
    return ball;
}