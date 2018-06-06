//
// Created by joao on 06/06/18.
//

#ifndef VSS_VISION_GAMEBUILDER_H
#define VSS_VISION_GAMEBUILDER_H

#include <Interfaces/IGameBuilder.h>

class GameBuilder : public IGameBuilder {
public:
    GameBuilder() = default;
    Game getInstance() override ;
};

#endif //VSS_VISION_GAMEBUILDER_H
