//
// Created by paulo on 06/05/18.
//

#include <Domain/ObjectType.h>

std::string toDescription(ObjectType objectType) {
    switch (objectType) {
        case ObjectType::Team:
            return "Team";
        case ObjectType::Opponent:
            return "Opponent";
        case ObjectType::Robot1:
            return "Robot1";
        case ObjectType::Robot2:
            return "Robot2";
        case ObjectType::Robot3:
            return "Robot3";
        case ObjectType::Robot4:
            return "Robot4";
        case ObjectType::Robot5:
            return "Robot5";
        case ObjectType::Ball:
            return "Ball";
        default:
            return "Unknown";
    }
}

ObjectType toObjectType(std::string objectType) {
    if (objectType == "Team")
        return ObjectType::Team;

    if (objectType == "Opponent")
        return ObjectType::Opponent;

    if (objectType == "Robot1")
        return ObjectType::Robot1;

    if (objectType == "Robot2")
        return ObjectType::Robot2;

    if (objectType == "Robot3")
        return ObjectType::Robot3;

    if (objectType == "Robot4")
        return ObjectType::Robot4;

    if (objectType == "Robot5")
        return ObjectType::Robot5;

    if (objectType == "Ball")
        return ObjectType::Ball;

    return ObjectType::Unknown;
}
