#ifndef VSS_VISION_GAME_H
#define VSS_VISION_GAME_H

#include <map>
#include "ColorType.h"
#include "WhoseName.h"

class Game {
public:
    Game();
    Game(Game * game);

    std::map<ColorType, WhoseName> whoseColor;
    std::string calibrationPath;
    std::map <ColorType, int> colorToIndex;
};

#endif //VSS_VISION_GAME_H
