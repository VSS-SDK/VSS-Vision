//
// Created by johnathan on 03/02/18.
//

#include "DirectoryHelper.h"

std::string getCurrentWorkingDir( void ) {
    char buff[FILENAME_MAX];
    getcwd( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

