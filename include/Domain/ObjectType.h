//
// Created by paulo on 06/05/18.
//

#ifndef VSS_VISION_OBJECT_TYPE_H
#define VSS_VISION_OBJECT_TYPE_H

#include "iostream"

enum class ObjectType {
    Unknown = 0,
    Team = 1,
    Opponent = 2,
    Robot1 = 3,
    Robot2 = 4,
    Robot3 = 5,
    Robot4 = 6,
    Robot5 = 7,
    Ball = 8
};

std::string toDescription(ObjectType);

ObjectType toObjectType(std::string);

#endif //VSS_VISION_OBJECT_TYPE_H
