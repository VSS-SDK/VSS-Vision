VSS-Vision 
==========
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)][gpl3]
[![Build Status](https://travis-ci.org/SIRLab/VSS-Vision.svg?branch=master)][travis]

> **Pay Attention and Follow All The Steps Bellow to Install VSS-Vision on Ubuntu 14.04 LTS 3, Ubuntu 16.04 LTS and Debian 8**

**Only Ubuntu 14.04 LTS** 
---------------------------
**Install Standard Packages:**
```
$ sudo apt-get update && apt-get upgrade
$ sudo apt-get install pkg-config
$ sudo apt-get install g++ cmake git x11-xserver-utils libglew1.10 libglew-dev freeglut3 freeglut3-dev uvcdynctrl libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev
```

**Only Ubuntu 16.04 LTS** 
---------------------------
**Install Standard Packages:**
```
$ sudo apt-get update && apt-get upgrade
$ sudo apt-get install pkg-config
$ sudo apt-get install g++ cmake git x11-xserver-utils libglew1.13 libglew-dev freeglut3 freeglut3-dev uvcdynctrl libzmqpp3 libzmqpp-dev protobuf-compiler libprotobuf-dev libxrandr-dev libxrandr-dev libxinerama-dev libxinerama1 libxcursor-dev libxcursor1
```

**Only Debian 8** 
---------------------------
**Install Standard Packages:**
```
$ sudo apt-get update && apt-get upgrade
$ sudo apt-get install pkgconf
$ sudo apt-get install g++ cmake git x11-xserver-utils libglew1.10 libglew-dev freeglut3 freeglut3-dev uvcdynctrl libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev
```

**All Distros** 
---------------------------

**Install GLFW 3:**
```
$ git clone https://github.com/glfw/glfw.git
$ cd glfw
$ git checkout latest
$ cmake . -DBUILD_SHARED_LIBS=ON
$ make -j8
$ sudo make install
$ sudo ldconfig
```

**Install OpenCV:**
```
$ git clone https://github.com/Itseez/opencv.git
$ cd opencv
$ cmake .
$ make -j8
$ sudo make install
$ sudo ldconfig
```

License
-------

This code is licensed under the [GNU GENERAL PUBLIC LICENSE Version 3][gpl3], of which a textual copy is available at [LICENSE.txt](LICENSE.txt).

You are allowed and encouraged to use this software on the IEEE Very Small Size Soccer competitions.  If you do, please let us know.

[gpl3]: http://www.gnu.org/licenses/gpl-3.0/
[sirface]: https://www.facebook.com/sirlab.faeterj/
[siryou]: https://www.youtube.com/channel/UCLXQhza5oA2EJYsYDbr41ZQ
[sirlink]: https://www.linkedin.com/company/sir-lab
[vss]: http://www.cbrobotica.org/
[protobuf]: https://developers.google.com/protocol-buffers/
[zmq]: http://zeromq.org/
[opencv]: http://opencv.org/
[glfw]: http://www.glfw.org/
[imgui]: https://github.com/ocornut/imgui/
[travis]: https://travis-ci.org/SIRLab/VSS-Vision
[samplestrategy]: https://github.com/SIRLab/VSS-SampleStrategy




