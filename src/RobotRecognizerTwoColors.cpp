//
// Created by manoel on 21/05/18.
//

#include <Helpers/Math.h>
#include "RobotRecognizerTwoColors.h"

RobotRecognizerTwoColors::RobotRecognizerTwoColors() {

    lastRobotsPos.resize(5, vss::Robot());

    blueRobots.resize(5, vss::Robot());
    yellowRobots.resize(5, vss::Robot());

    lastBallPos = vss::Ball();

    // 1/60
    rate = 0.016;
}

std::vector<vss::Robot> RobotRecognizerTwoColors::recognizeTeam(std::vector< std::vector<ColorPosition>>& teamColorPositions, ColorType teamColor){

    blueRobots.clear();
    yellowRobots.clear();

    blueRobots.resize(5);
    yellowRobots.resize(5);

    std::vector<vss::Robot> teamRobots(5, vss::Robot());

    for(auto& blob : teamColorPositions){

        cv::Point2f teamPosition;
        std::vector<cv::Point2f> greenPositions;
        std::vector<cv::Point2f> pinkPositions;

        for(auto& p : blob){
            if(p.color == ColorType::Pink) {
                pinkPositions.insert(pinkPositions.begin(), p.points.begin(), p.points.end());
            } else if(p.color == ColorType::Green) {
                greenPositions.insert(greenPositions.begin(), p.points.begin(), p.points.end());
            } else if (p.color == teamColor){
                teamPosition = p.points.front();
            }
        }

        unsigned long numberPinkPoints = pinkPositions.size();
        unsigned long numberGreenPoints = greenPositions.size();

        // de acordo com a quantidade de cores verde e rosa determina qual e o robo
        if(numberPinkPoints == 1 and numberGreenPoints == 1){
            vss::Robot robot = buildRobot1(teamPosition, greenPositions, pinkPositions);
            teamRobots[0] = robot;

        } else if(numberPinkPoints == 1 and numberGreenPoints == 2){
            vss::Robot robot = buildRobot2(teamPosition, greenPositions, pinkPositions);
            teamRobots[1] = robot;

        } else if(numberPinkPoints == 2 and numberGreenPoints == 1){
            vss::Robot robot = buildRobot3(teamPosition, greenPositions, pinkPositions);
            teamRobots[2] = robot;

        }
    }

    if(teamColor == ColorType::Blue){
        blueRobots = teamRobots;
    } else if(teamColor == ColorType::Yellow){
        yellowRobots = teamRobots;
    }

    return teamRobots;
}

std::vector<vss::Robot> RobotRecognizerTwoColors::recognizeOpponent(ColorPosition& opponentColorPositions, ColorType opponentColor){

    std::vector<vss::Robot> opponentsRobots;

    for (auto &point : opponentColorPositions.points) {
        vss::Robot robot = buildOpponent(point);
        opponentsRobots.emplace_back(robot);
    }

    opponentsRobots.resize(5);

    if(opponentColor == ColorType::Blue){
        blueRobots = opponentsRobots;
    } else if(opponentColor == ColorType::Yellow){
        yellowRobots = opponentsRobots;
    }

    return opponentsRobots;

}

vss::Ball RobotRecognizerTwoColors::recognizeBall(ColorPosition& ballPosition){

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

vss::Robot RobotRecognizerTwoColors::buildRobot1(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){
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

vss::Robot RobotRecognizerTwoColors::buildRobot2(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){
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

vss::Robot RobotRecognizerTwoColors::buildRobot3(cv::Point2f& teamPoint, std::vector<cv::Point2f>& greenPositions, std::vector<cv::Point2f>& pinkPositions){
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

vss::Robot RobotRecognizerTwoColors::buildOpponent(cv::Point2f& p){
    vss::Robot vssRobot;
    vssRobot.x = p.x;
    vssRobot.y = p.y;

    return vssRobot;
}

float RobotRecognizerTwoColors::calculateAngle(cv::Point2f robotPos, cv::Point2f teamPos){
    // somando 180 para deixar no intervalo 0 e 360
    float angle = atan2(robotPos.y - teamPos.y, robotPos.x - teamPos.x)*(180/M_PI)+180;

    if(angle >= 315) angle -= 315;
    else angle += 45;

    return angle;
}

std::vector<vss::Robot> RobotRecognizerTwoColors::getBlueRobots(){
    return blueRobots;
}

std::vector<vss::Robot> RobotRecognizerTwoColors::getYellowRobots(){
    return yellowRobots;
}

vss::Ball RobotRecognizerTwoColors::getBall(){
    return ball;
}
