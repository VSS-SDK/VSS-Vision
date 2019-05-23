//
// Created by manoel on 02/02/19.
//

#include <Helpers/RobotHelper.h>

bool isEmpty(vss::Robot robot){
    return robot.x == 0 and robot.y == 0;
}

bool isEmpty(vss::Ball ball){
    return ball.x == 0 and ball.y == 0;
}

bool isEmpty(vss::Point point){
    return point.x == 0 and point.y == 0;
}