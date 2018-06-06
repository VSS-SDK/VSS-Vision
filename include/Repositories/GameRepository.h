#ifndef VSS_VISION_GAMEREPOSITORY_H
#define VSS_VISION_GAMEREPOSITORY_H

#include <Interfaces/IGameRepository.h>
#include <fstream>
#include <Interfaces/IGameBuilder.h>

class GameRepository : public IGameRepository {
public:
    GameRepository(IGameBuilder *gameFactory);
    Game read(std::string pathName, std::map <WhoseName, Gtk::ComboBox*> whoseNameToComboBox) override;
    void create(std::string pathName, Game game) override;
private:
    IGameBuilder * gameBuilder;
};

#endif //VSS_VISION_GAMEREPOSITORY_H
