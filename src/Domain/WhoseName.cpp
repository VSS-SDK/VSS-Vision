//
// Created by paulo on 06/05/18.
//

#include <Domain/WhoseName.h>

std::string toDescription(WhoseName whoseName) {
    switch (whoseName) {
        case WhoseName::Team:
            return "Team";
        case WhoseName::Opponent:
            return "Opponent";
        case WhoseName::Robot1:
            return "Robot1";
        case WhoseName::Robot2:
            return "Robot2";
        case WhoseName::Robot3:
            return "Robot3";
        case WhoseName::Robot4:
            return "Robot4";
        case WhoseName::Robot5:
            return "Robot5";
        case WhoseName::Ball:
            return "Ball";
        default:
            return "Unknown";
    }
}

WhoseName toWhoseName(std::string whoseName) {
    if (whoseName == "Team")
        return WhoseName::Team;

    if (whoseName == "Opponent")
        return WhoseName::Opponent;

    if (whoseName == "Robot1")
        return WhoseName::Robot1;

    if (whoseName == "Robot2")
        return WhoseName::Robot2;

    if (whoseName == "Robot3")
        return WhoseName::Robot3;

    if (whoseName == "Robot4")
        return WhoseName::Robot4;

    if (whoseName == "Robot5")
        return WhoseName::Robot5;

    if (whoseName == "Ball")
        return WhoseName::Ball;

    return WhoseName::Unknown;
}
