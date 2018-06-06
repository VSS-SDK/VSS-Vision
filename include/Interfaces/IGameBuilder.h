//
// Created by joao on 06/06/18.
//

#ifndef VSS_VISION_IGAMEBUILDER_H
#define VSS_VISION_IGAMEBUILDER_H

#include <Domain/Game.h>

class IGameBuilder{
public:
    virtual Game getInstance() = 0;
};

#endif //VSS_VISION_IGAMEBUILDER_H
