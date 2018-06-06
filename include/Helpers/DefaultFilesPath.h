//
// Created by manoel on 03/06/18.
//

#ifndef VSS_VISION_DEFAULTFILESPATH_H
#define VSS_VISION_DEFAULTFILESPATH_H

#include <iostream>

const std::string pathFolder = ".vss-files";
const std::string defaultFilesPath = std::string(getenv("HOME")) + "/" + pathFolder;

#endif //VSS_VISION_DEFAULTFILESPATH_H