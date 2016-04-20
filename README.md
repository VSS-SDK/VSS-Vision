VSS-Vision 
==========
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)][gpl3]
[![Build Status](https://travis-ci.org/SIRLab/VSS-Vision.svg?branch=master)][travis]

Description
-----------
Esse é um protótipo de um programa de Visão Computacional global para a competição de futebol de robôs [IEEE Very Small Size (VSS)][vss], começou a ser desenvolvido em 01/2016 pelo [Laboratório de Sistemas Inteligentes de Robótica (SIRLab)][sirface] e aberto 04/2016 sob a licença GLP versão 3.0. O programa utiliza o protocolo [Protobuf][protobuf] para enviar e receber dados via socket utilizando a biblioteca [ZMQ][zmq], oferece uma maneira simples de calibragem utilizando a biblioteca [OpenCV][opencv] e um ambiente gráfico 3D utilizando a biblioteca [glfw][glfw], além de telas interativas criadas com auxílio da biblioteca [ImGui][imgui].

> Um exemplo de estratégia que obtem os dados do VSS-Vision encontra-se em [VSS-SampleStrategy][samplestrategy].


**Install** Ubuntu (14.04 LTS)
------------------------------
```
$ sudo apt-get install g++ cmake git libopencv-dev x11-xserver-utils libglfw2 libglew1.10 libglew-dev freeglut3 freeglut3-dev uvcdynctrl arduino putty libbullet-dev libzmq3 libzmq3-dev protobuf-compiler libprotobuf-dev
```

> TODO: Install para Debian e Fedora.

Developing
----------
```
make && make run
```


Release
-------
```
O projeto está em construção. Ainda não é possível utilizá-lo.

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




