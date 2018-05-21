//
// Created by manoel on 21/05/18.
//

#include <Helpers/Math.h>
#include "RobotRecognizer.h"

void RobotRecognizer::recognizeRobots(std::map<WhoseName, ColorPosition> colors) {

    // iterate through team1 colors and team2 colors
    for(int i=1 ; i<=2 ; i++) {

        // team colors positions
        auto teamPositions = colors[(WhoseName) i];

        // iterate through robot1 color, robot2, ... etc
        for (int j = 3; j <= 7; j++) {

            auto name = (WhoseName) j;

            if (colors[name].color != ColorType::UnknownType) {
                int idTeamColor = -1;
                int idRobotColor = -1;
                double shorterDistance = 10000;

                for (unsigned int k = 0; k < colors[name].points.size(); k++) {
                    // looks for the color with the shorter distance in team colors positions vector
                    for (unsigned int l = 0; l < teamPositions.points.size(); l++) {
                        // talvez adicionar uma distancia maxima para ser considerado robo
                        double distance = Math::distance(colors[name].points[k], teamPositions.points[l]);
                        if (distance < shorterDistance) {
                            shorterDistance = distance;
                            idRobotColor = k;
                            idTeamColor = l;
                        }
                    }
                }

                // with the closer point found update robot's values
                vss::Robot robot;
                cv::Point midPoint = Math::midPoint(colors[name].points[idRobotColor],
                                                    teamPositions.points[idTeamColor]);
                robot.x = midPoint.x;
                robot.y = midPoint.y;
                //@TODO verificar angulacao
                robot.angle = atan2(colors[name].points[idRobotColor].y - teamPositions.points[idTeamColor].y,
                                    colors[name].points[idRobotColor].x - teamPositions.points[idTeamColor].x) *
                              (180 / CV_PI);
                //robot.speedAngle = ...
                //robot.speedX = ...
                //robot.speedY = ...

                // remove used point to optimize searching
                teamPositions.points.erase(teamPositions.points.begin() + idTeamColor);

                robots.push_back(robot);
            }
        }
    }
}


std::vector<vss::Robot> RobotRecognizer::getRobots() {
    return robots;
}
