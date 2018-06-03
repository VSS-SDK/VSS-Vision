#!/bin/bash
#
# This file is part of the VSS-SDK project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

INSTALL_CORE () {
    apt-get update && apt-get upgrade
    apt-get -y install git

    git clone https://github.com/SIRLab/VSS-Core.git
    cd VSS-Core
    bash configure.sh
}

INSTALL_CORE;