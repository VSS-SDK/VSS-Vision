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
}

void RobotRecognizer::recognizeTeam(ColorPosition teamColor, std::vector<ColorPosition> playerColor, std::vector<ColorPattern> pattern){
    for (unsigned int i = 0; i < teamColor.points.size(); i++){

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
            }else{
                farthestColorIndex = 1;
            }

        }else if(dist02 < dist01 && dist02 < dist12){
            singleColorIndex = 1;

            if (dist01 < dist12){
                closestColorIndex = 0;
            }else{
                farthestColorIndex = 2;
            }
        }else if(dist12 < dist01 && dist12 < dist01){
            singleColorIndex = 0;

            if(dist01 < dist02){
                closestColorIndex = 1;
            }else{
                farthestColorIndex = 2;
            }
        }

        double closestAngle = Math::angle(playerColor[i].points[singleColorIndex], playerColor[i].points[closestColorIndex]);
        double farthestAngle = Math::angle(playerColor[i].points[singleColorIndex], playerColor[i].points[farthestColorIndex]);

        std::cout << closestAngle << " - " << farthestAngle << std::endl;

        ColorSide colorSide = recognizeSide(farthestAngle, closestAngle);

        ColorPattern colorPattern;
        colorPattern.colorSide = colorSide;
        colorPattern.singleColorType = playerColor[i].color;
        colorPattern.doubleColorType = playerColor[i].color;

        vss::Robot robot;
        robot.x = teamColor.points[i].x;
        robot.y = teamColor.points[i].y;
        robot.angle = farthestAngle;

        //std::cout << colorPattern.colorSide << std::endl;
        //std::cout << colorPattern.singleColorType << std::endl;
        //std::cout << colorPattern.doubleColorType << std::endl << std::endl;

        for(unsigned int j = 3; j < pattern.size() - 1; j++){

            if(pattern[j].isEquals(colorPattern)){
                if(teamColor.color == ColorType::Blue){
                    blueRobots[j-3] = robot;
                }else if(teamColor.color == ColorType::Yellow){
                    yellowRobots[j-3] = robot;
                }
            }
        }
    }
    std::cout << std::endl;
    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());

/*
    for (unsigned int j = 0; j < pattern.size(); j++ ) {
        std::cout << j << ": " << pattern[j].colorSide << std::endl;
        std::cout << j << ": " << pattern[j].singleColorType << std::endl;
        std::cout << j << ": " << pattern[j].doubleColorType << std::endl << std::endl;
    }
*/
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
}


ColorSide RobotRecognizer::recognizeSide(double farthestAngle, double closestAngle) {
    farthestAngle = farthestAngle + 360;
    closestAngle = closestAngle + 360;

    double max1 = farthestAngle + 60;
    double min1 = farthestAngle + 30;

    double max2 = farthestAngle - 60;
    double min2 = farthestAngle - 30;

    ColorSide colorSide;

    if(closestAngle < max1 && closestAngle > min1){
        colorSide = ColorSide::Right;
    }

    if(closestAngle < max2 && closestAngle > min2){
        colorSide = ColorSide ::Left;
    }

    return colorSide;
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
