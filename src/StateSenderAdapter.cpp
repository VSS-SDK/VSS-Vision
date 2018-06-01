//
// Created by manoel on 01/06/18.
//

#include "StateSenderAdapter.h"

StateSenderAdapter::StateSenderAdapter() = default;

void StateSenderAdapter::createSocket() {
    sender.createSocket();
}

void StateSenderAdapter::sendState(std::vector<vss::Robot>& robots, vss::Ball& ball) {
    vss::State state;
    unsigned long nRobots = robots.size()/2;

    state.ball = ball;
    state.teamYellow.insert(state.teamYellow.end(), robots.begin(), robots.begin()+nRobots);
    state.teamBlue.insert(state.teamBlue.end(), robots.begin()+nRobots, robots.end());

//    std::cout << state << std::endl;

    sender.sendState(state);
}