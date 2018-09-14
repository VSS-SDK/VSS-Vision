//
// Created by manoel on 01/06/18.
//

#include <Domain/Constants.h>
#include "StateSenderAdapter.h"

StateSenderAdapter::StateSenderAdapter(){
    sender = new vss::StateSender();
};

void StateSenderAdapter::createSocket(vss::ExecutionConfig &exeConfig) {
    if(exeConfig.stateSendAddr.getIp() != vss::DEFAULT_STATE_SEND_ADDR || exeConfig.stateSendAddr.getPort() != vss::DEFAULT_STATE_PORT)
        sender->createSocket(exeConfig.stateSendAddr);
    else
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