//
// Created by manoel on 21/05/18.
//

#include <Helpers/Math.h>
#include "RobotRecognizer.h"

RobotRecognizer::RobotRecognizer() {

    lastRobotsPos.resize(5, vss::Robot());

    lastBallPos = vss::Ball();

    // 1/60
    rate = 0.016;
}

std::vector<vss::Robot> RobotRecognizer::recognizeTeam(std::vector< std::vector<ColorPosition>>& teamRobots, ColorType teamColor){

    for(auto& blob : teamRobots){

        cv::Point2f teamPosition;
        std::vector<cv::Point2f> greenPositions;
        std::vector<cv::Point2f> pinkPositions;

        for(auto& p : blob){
            if(p.color == ColorType::Pink) {
                pinkPositions.emplace_back(p.points[0]);
            } else if(p.color == ColorType::Green) {
                greenPositions.emplace_back(p.points[0]);
            } else {
                teamPosition = p.points[0];
                teamColor = p.color;
            }
        }

        unsigned long numberPinkPoints = pinkPositions.size();
        unsigned long numberGreenPoints = greenPositions.size();

        // de acordo com a quantidade de cores verde e rosa determina qual e o robo
        if(numberPinkPoints == 1 and numberGreenPoints == 1){
            vss::Robot robot = buildRobot1(teamPosition, greenPositions, pinkPositions);

            if(teamColor == ColorType::Blue) blueRobots[0] = robot;
            else yellowRobots[0] = robot;

        } else if(numberPinkPoints == 1 and numberGreenPoints == 2){
            vss::Robot robot = buildRobot2(teamPosition, greenPositions, pinkPositions);

            if(teamColor == ColorType::Blue) blueRobots[1] = robot;
            else yellowRobots[1] = robot;

        } else if(numberPinkPoints == 2 and numberGreenPoints == 1){
            vss::Robot robot = buildRobot3(teamPosition, greenPositions, pinkPositions);

            if(teamColor == ColorType::Blue) blueRobots[2] = robot;
            else yellowRobots[2] = robot;

        } else {

            if(teamColor == ColorType::Blue) blueRobots[2] = vss::Robot();
            else yellowRobots[2] = vss::Robot();

        }
    }

    if(teamColor == ColorType::Blue){
        blueRobots.resize(5, vss::Robot());
        return blueRobots;
    }

    yellowRobots.resize(5, vss::Robot());
    return yellowRobots;
}

std::vector<vss::Robot> RobotRecognizer::recognizeOpponent(std::vector< std::vector<ColorPosition>>& opponentRobots, ColorType opponentColor){

    for (auto &blob : opponentRobots) {
        for (auto &p : blob) {
            vss::Robot robot = buildOpponent(p.points[0]);

            if (opponentColor == ColorType::Blue) blueRobots.emplace_back(robot);
            else yellowRobots.emplace_back(robot);
        }
    }

    if(opponentColor == ColorType::Blue){
        blueRobots.resize(5);
        return blueRobots;
    }

    yellowRobots.resize(5);
    return yellowRobots;

}

vss::Ball RobotRecognizer::recognizeBall(ColorPosition& ballPosition){

    // calculates ball values
    if(not ballPosition.points.empty()) {
        ball.x = ballPosition.points.front().x;
        ball.y = ballPosition.points.front().y;

        ball.speedX = (ball.x - lastBallPos.x) / rate;
        ball.speedY = (ball.y - lastBallPos.y) / rate;

        lastBallPos = ball;
    }

    return ball;
}

vss::Robot RobotRecognizer::buildRobot1(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){

    vss::Robot vssRobot;
    vssRobot.x = teamPoint.x;
    vssRobot.y = teamPoint.y;

    vssRobot.angle = calculateAngle(greenPositions[0], pinkPositions[0]);

    vssRobot.speedAngle = (vssRobot.angle - lastRobotsPos[0].angle) / rate;
    vssRobot.speedX = (vssRobot.x - lastRobotsPos[0].x) / rate;
    vssRobot.speedY = (vssRobot.y - lastRobotsPos[0].y) / rate;

    lastRobotsPos[0] = vssRobot;

    return vssRobot;
}

vss::Robot RobotRecognizer::buildRobot2(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){
    vss::Robot vssRobot;

    vssRobot.x = teamPoint.x;
    vssRobot.y = teamPoint.y;

    auto distantGreenPoint = [&](){
        // procura pelo ponto verde mais distante do rosa

        double maxDistance = -1;
        cv::Point2f distantPoint;

        for(auto& i : greenPositions){
            double distance = Math::distance(i, pinkPositions[0]);
            if(distance > maxDistance){
                maxDistance = distance;
                distantPoint = i;
            }
        }

        return distantPoint;
    }();

    vssRobot.angle = calculateAngle(distantGreenPoint, pinkPositions[0]);

    vssRobot.speedAngle = (vssRobot.angle - lastRobotsPos[1].angle) / rate;
    vssRobot.speedX = (vssRobot.x - lastRobotsPos[1].x) / rate;
    vssRobot.speedY = (vssRobot.y - lastRobotsPos[1].y) / rate;

    lastRobotsPos[1] = vssRobot;

    return vssRobot;
}

vss::Robot RobotRecognizer::buildRobot3(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){
    vss::Robot vssRobot;

    vssRobot.x = teamPoint.x;
    vssRobot.y = teamPoint.y;

    auto distantPinkPoint = [&](){
        // procura pelo ponto rosa mais distante do verde

        double maxDistance = -1;
        cv::Point2f distantPoint;

        for(auto& i : pinkPositions){
            double distance = Math::distance(i, greenPositions[0]);
            if(distance > maxDistance){
                maxDistance = distance;
                distantPoint = i;
            }
        }

        return distantPoint;
    }();

    vssRobot.angle = calculateAngle(distantPinkPoint, greenPositions[0]);

    vssRobot.speedAngle = (vssRobot.angle - lastRobotsPos[2].angle) / rate;
    vssRobot.speedX = (vssRobot.x - lastRobotsPos[2].x) / rate;
    vssRobot.speedY = (vssRobot.y - lastRobotsPos[2].y) / rate;

    lastRobotsPos[2] = vssRobot;

    return vssRobot;
}

vss::Robot RobotRecognizer::buildOpponent(cv::Point2f& p){
    vss::Robot vssRobot;
    vssRobot.x = p.x;
    vssRobot.y = p.y;

    return vssRobot;
}

float RobotRecognizer::calculateAngle(cv::Point2f robotPos, cv::Point2f teamPos){
    // somando 180 para deixar no intervalo 0 e 360
    float angle = atan2(robotPos.y - teamPos.y, robotPos.x - teamPos.x)*(180/M_PI)+180;

    if(angle >= 315) angle -= 315;
    else angle += 45;

    return angle;
}

vss::Robot RobotRecognizer::calculateRobotsValues(cv::Point2f teamPos, cv::Point2f robotPos, ObjectType robotNumber) {
    // with the closer point found update robot's values
    vss::Robot robot;

    robot.x = teamPos.x;
    robot.y = teamPos.y;

    // somando 180 para deixar no intervalo 0 e 360
    robot.angle = atan2(robotPos.y - teamPos.y, robotPos.x - teamPos.x)*(180/M_PI)+180;

    if(robot.angle >= 315) robot.angle -= 315;
    else robot.angle += 45;

    robot.speedAngle = (robot.angle - lastRobotsPos[robotNumber].angle) / rate;
    robot.speedX = (robot.x - lastRobotsPos[robotNumber].x) / rate;
    robot.speedY = (robot.y - lastRobotsPos[robotNumber].y) / rate;

    return robot;
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
