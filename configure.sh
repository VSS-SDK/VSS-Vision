#!/bin/bash
#
# This file is part of the VSS-SDK project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

DISTRO=`lsb_release -si`
RELEASE=`lsb_release -sr`
RELEASE_DEBIAN=`lsb_release -sr | cut -c1-1`
ARCHITECTURE=`uname -m`

INSTALLED=0

CMAKE_UBUNTU () {
  sudo rm -R build
  mkdir build
  cd build
  cmake ..
  make package
  sudo dpkg -i vss-vision-0.1.1-Linux.deb
  cd ..
}

CMAKE_MINT () {
  sudo rm -R build
  mkdir build
  cd build
  cmake ..
  make package
  sudo dpkg -i vss-vision-0.1.1-Linux.deb
  cd ..
}

CMAKE_DEBIAN () {
  rm -R build
  mkdir build
  cd build
  cmake ..
  make package
  dpkg -i vss-vision-0.1.1-Linux.deb
  cd ..
}

INSTALL_UBUNTU_14_04 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev libopencv-dev build-essential checkinstall yasm libtiff4-dev libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libtbb-dev libqt4-dev libgtk2.0-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils ffmpeg
  INSTALLED=1
}

INSTALL_UBUNTU_16_04 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev libopencv-dev gtkmm-2.4 
  INSTALLED=1
}

INSTALL_MINT_18_2 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkg-config
  sudo apt-get install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev libopencv-dev libgtkmm-2.4-dev
  INSTALLED=1
}

INSTALL_DEBIAN_9 () {
  sudo apt-get update && apt-get upgrade
  sudo apt-get install pkgconf
  sudo apt-get install g++ cmake protobuf-compiler libprotobuf-dev libboost-all-dev libopencv-dev libgtkmm-2.4-dev gtk2-engines-pixbuf
  INSTALLED=1
}

INSTALL () {
  # Ubuntu
  if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "16.04" ]]; then
    INSTALL_UBUNTU_16_04;
    if [ $INSTALLED == 1 ]; then
      CMAKE_UBUNTU;
    fi
  fi

  if [[ "$DISTRO" == "Ubuntu" ]] && [[ "$RELEASE" == "14.04" ]]; then
    INSTALL_UBUNTU_14_04;
    if [ $INSTALLED == 1 ]; then
      CMAKE_UBUNTU;
    fi
  fi

  # Debian
  if [[ "$DISTRO" == "Debian" ]]&& [[ "$RELEASE_DEBIAN" == "9" ]]; then
    INSTALL_DEBIAN_9;
    if [ $INSTALLED == 1 ]; then
      CMAKE_DEBIAN;
    fi
  fi

  # LinuxMint
  if [[ "$DISTRO" == "LinuxMint" ]]; then
    INSTALL_MINT_18_2;
    if [ $INSTALLED == 1 ]; then
      CMAKE_MINT;
    fi
  fi

  if [[ $INSTALLED == 0 ]]; then
    echo "Sistema Operacional Incompatível";
  fi
}

INSTALL;
