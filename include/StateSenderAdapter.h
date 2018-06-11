//
// Created by manoel on 01/06/18.
//

#ifndef VSS_VISION_STATESENDERADAPTER_H
#define VSS_VISION_STATESENDERADAPTER_H

#include <Interfaces/IStateSender.h>
#include <Communications/StateSender.h>
#include <Domain/State.h>
#include "Domain/Robot.h"
#include "Domain/Ball.h"
#include "IStateSenderAdapter.h"

class StateSenderAdapter : public IStateSenderAdapter {

public:

    StateSenderAdapter();
    void createSocket() override;
    void sendState(std::vector<vss::Robot>& blueRobots, std::vector<vss::Robot>& yellowRobots, vss::Ball& ball) override;

private:

    vss::IStateSender* sender;

};

#endif //VSS_VISION_STATESENDERADAPTER_H
