#!/bin/bash
#
# This file is part of the VSS-SDK project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

DISTRO=``
RELEASE=``
RELEASE_DEBIAN=``
ARCHITECTURE=``
COMPILE_TYPE=$1

INSTALLED=0

CMAKE () {
    rm -R build
    mkdir -p build
    cd build
    cmake ..
    make
    cd ..
}

CMAKE_INSTALL () {
    rm -R build
    mkdir -p build
    cd build
    cmake -D RELEASE=ON ..
    make install
    cd ..
}

INSTALL_UBUNTU_14_04 () {
    apt-get update && apt-get upgrade
    apt-get -y install build-essential libgtkmm-3.0-dev checkinstall yasm libtiff4-dev libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libtbb-dev libqt4-dev libgtk2.0-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils ffmpeg
    INSTALLED=1
}

INSTALL_UBUNTU_16_04 () {
    apt-get update && apt-get upgrade
    apt-get -y install libgtkmm-3.0-dev
    INSTALLED=1
}

INSTALL_UBUNTU_18_04 () {
    apt-get update && apt-get upgrade
    apt-get -y install pkg-config
    apt-get -y install libgtkmm-3.0-dev
    INSTALLED=1
}

INSTALL_MINT_18_2 () {
    apt-get update && apt-get upgrade
    apt-get -y install pkg-config
    apt-get -y install libgtkmm-3.0-dev
    INSTALLED=1
}

INSTALL_DEBIAN_9 () {
    apt-get update && apt-get upgrade
    apt-get -y install pkgconf
    apt-get -y install libopencv-dev libgtkmm-3.0-dev
    INSTALLED=1
}

INSTALL_BASE() {
    apt-get update && apt-get upgrade
    apt-get -y install lsb-release;

    DISTRO=`lsb_release -si`
    RELEASE=`lsb_release -sr`
    RELEASE_DEBIAN=`lsb_release -sr | cut -c1-1`
    ARCHITECTURE=`uname -m`
}

INSTALL_OPENCV3 () {
    git clone https://github.com/opencv/opencv.git
    cd opencv
    mkdir build
    cd build
    cmake ..
    make -j4
    make install
    sudo ldconfig
    rm -rf opencv
}

INIT_SUBMODULES() {
    git submodule init;
    git submodule update;
}

INSTALL () {
    INSTALL_BASE;

    # Ubuntu
    if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "16.04" ]]; then
        INSTALL_UBUNTU_16_04;
    fi

    if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "14.04" ]]; then
        INSTALL_UBUNTU_14_04;
    fi

    # Debian
    if [[ "$DISTRO" == "Debian" ]]&& [[ "$RELEASE_DEBIAN" == "9" ]]; then
        INSTALL_DEBIAN_9;
    fi

    # LinuxMint
    if [[ "$DISTRO" == "LinuxMint" ]]; then
        INSTALL_MINT_18_2;
    fi

    if [[ $INSTALLED == 0 ]]; then
        echo "Sistema Operacional Incompatível";
    fi

    if [[ $INSTALLED == 1 ]]; then
        INIT_SUBMODULES;

        if [[ $COMPILE_TYPE == "development" ]];
        then
            CMAKE;
        else
            CMAKE_INSTALL;
        fi
    fi
}

INSTALL;
