//
// Created by paulo on 06/05/18.
//

#ifndef VSS_VISION_WHOSENAME_H
#define VSS_VISION_WHOSENAME_H

#include "iostream"

enum WhoseName {
    Unknown = 0,
    Team1 = 1,
    Team2 = 2,
    Robot1 = 3,
    Robot2 = 4,
    Robot3 = 5,
    Robot4 = 6,
    Robot5 = 7,
    Ball = 8
};

std::string toDescription(WhoseName);

WhoseName toWhoseName(std::string);

#endif //VSS_VISION_WHOSENAME_H
