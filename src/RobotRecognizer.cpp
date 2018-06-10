//
// Created by manoel on 21/05/18.
//

#include <Helpers/Math.h>

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
    // max distance in cm between colors to be considered a robot
    maxDistance = 10;
}

void RobotRecognizer::recognizeRobots(std::map<WhoseName, ColorPosition> colorsPos) {

    blueRobots.clear();
    yellowRobots.clear();

    if(not colorsPos.empty()) {
        recognizeTeam(colorsPos);
        recognizeOpponent(colorsPos);
        recognizeBall(colorsPos);
    }

    // fill each vector with 3 robots
    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());

}

void RobotRecognizer::recognizeTeam(std::map<WhoseName,ColorPosition>& colors){

    auto &teamPositions = colors[WhoseName::Team].points;
    auto &teamColor = colors[WhoseName::Team].color;

    if (teamColor == ColorType::UnknownType or teamPositions.empty()) return;

//    std::cout << "TEAM:" << std::endl;
//    for(auto i : teamPositions){
//        std::cout << i << std::endl;
//    }
    //std::cout << std::endl;

    // iterate through robots
    for (int robotInt = WhoseName::Robot1; robotInt <= WhoseName::Robot5; robotInt++) {

        auto robotNumber = static_cast<WhoseName>(robotInt);

        auto &robotPositions = colors[robotNumber].points;
        auto &robotColor = colors[robotNumber].color;

        if (robotColor == ColorType::UnknownType or robotPositions.empty()){
            if(teamColor == ColorType::Yellow)
                yellowRobots.emplace_back(vss::Robot());
            else
                blueRobots.emplace_back(vss::Robot());

            continue;
        }

//        std::cout << "ROBOT:" << std::endl;
//        for(auto i : robotPositions){
//            std::cout << i << std::endl;
//        }
        //std::cout << std::endl;

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

            if(itRobotPos != robotPositions.end()) break;
        }

        // with the closer point found update robot's values
        vss::Robot robot;
        if (itRobotPos != robotPositions.end() and itTeamPos != teamPositions.end()) {
            robot.x = itTeamPos->x;
            robot.y = itTeamPos->y;

            // somando 180 para deixar no intervalo 0 e 360
            robot.angle = atan2(itRobotPos->y - itTeamPos->y, itRobotPos->x - itTeamPos->x)*(180/M_PI)+180;

            if(robot.angle >= 315) robot.angle -= 315;
            else robot.angle += 45;

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

void RobotRecognizer::recognizeOpponent(std::map<WhoseName,ColorPosition>& colors){

    auto &opponentPositions = colors[WhoseName::Team].points;
    auto &opponentColor = colors[WhoseName::Team].color;

    if (opponentColor == ColorType::UnknownType or opponentPositions.empty()) return;

    for(auto opponentPoint : opponentPositions){

        vss::Robot robot;

        robot.x = opponentPoint.x;
        robot.y = opponentPoint.y;

        //@TODO: calcular velocidade dos adversarios

        if(opponentColor == ColorType::Blue)
            blueRobots.push_back(robot);
        else
            yellowRobots.push_back(robot);
    }
}

void RobotRecognizer::recognizeBall(std::map<WhoseName,ColorPosition>& colors){

    // calculates ball values
    if(not colors[WhoseName::Ball].points.empty()) {
        ball.x = colors[WhoseName::Ball].points.front().x;
        ball.y = colors[WhoseName::Ball].points.front().y;

        ball.speedX = (ball.x - lastBallPos.x) / rate;
        ball.speedY = (ball.y - lastBallPos.y) / rate;

        lastBallPos = ball;
    }

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
