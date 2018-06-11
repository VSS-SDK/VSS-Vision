//
// Created by manoel on 01/06/18.
//

#include "StateSenderAdapter.h"

StateSenderAdapter::StateSenderAdapter(){
    sender = new vss::StateSender();
};

void StateSenderAdapter::createSocket() {
    sender->createSocket();
}

void StateSenderAdapter::sendState(std::vector<vss::Robot>& blueRobots, std::vector<vss::Robot>& yellowRobots, vss::Ball& ball) {
    vss::State state;

    state.ball = ball;
    state.teamYellow.insert(state.teamYellow.end(), yellowRobots.begin(), yellowRobots.end());
    state.teamBlue.insert(state.teamBlue.end(), blueRobots.begin(), blueRobots.end());

//    std::cout << state << std::endl;

    sender->sendState(state);
}