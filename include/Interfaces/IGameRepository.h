#ifndef VSS_VISION_IGAMEREPOSITORY_H
#define VSS_VISION_IGAMEREPOSITORY_H

#include <Domain/Game.h>
#include <gtkmm/combobox.h>


class IGameRepository {
public:
    virtual Game read(std::string pathName, std::map <WhoseName, Gtk::ComboBox*> whoseNameToComboBox) = 0;
    virtual void create(std::string pathName, Game game) = 0;
};

#endif //VSS_VISION_IGAMEREPOSITORY_H
