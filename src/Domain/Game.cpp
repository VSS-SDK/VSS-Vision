/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */
#include <Domain/Game.h>

 Game::Game() {
     colorToIndex.clear();
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::UnknownType, -1));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Blue, 0));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Yellow, 1));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Green, 0));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Pink, 1));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Purple, 2));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Red, 3));
     colorToIndex.insert(std::pair<ColorType, int>(ColorType::Brown, 4));
 }

 Game::Game(Game *game) {
     this->colorToIndex = game->colorToIndex;
     this->whoseColor = game->whoseColor;
     this->calibrationPath = game->calibrationPath;
 }