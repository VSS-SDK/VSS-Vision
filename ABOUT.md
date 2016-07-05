VSS-Vision 
==========
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)][gpl3]
[![Build Status](https://travis-ci.org/SIRLab/VSS-Vision.svg?branch=master)][travis]

Mais informações sobre o framework podem ser encontradas em [sirlab.github.io][sirlab_site].


Technical Aspects
-----------------
Aspectos técnicos do funcionamento do sistema.

#### Input Data (Entrada de Dados) ####
Nessa seção é escolhido a entrada de dados do sistema, ou seja, as imagens que iram alimentar o algorimo de visão computacional, existem três opções: Camera, Imagem salva e Video Salvo. Como pode ser visto na figura abaixo.

![screenshot 1](https://raw.githubusercontent.com/SIRLab/VSS-Vision/master/images/input_data.png)

O sistema automáticamente reconhece qualquer camera USB conectada a qualquer distro Linux (Testado em Ubuntu 14.04, Ubuntu 16.04, Debian 8, Fedora 21 e Raspbian), caso não haja nenhuma camera o mesmo desabilita a opção de escolha. O mesmo funciona para as imagens salvas e videos salvos, o programa procura imagens no diretório **VSS-Vision/src/images** e videos em **VSS-Vision/src/videos**.

TODO
----
* Adicionar a Interface ZMQ + Protobuf ao sistema
* Adicionar filtro de kalman no algoritmo de visão
* Adicionar otimização de secção no algoritmo de visão



[protobuf]: https://developers.google.com/protocol-buffers/
[zmq]: http://zeromq.org/
[opencv]: http://opencv.org/
[glfw]: http://www.glfw.org/
[imgui]: https://github.com/ocornut/imgui/
[qt]: https://www.qt.io/

[gpl3]: http://www.gnu.org/licenses/gpl-3.0/
[documentation]: http://sirlab.github.io/assets/docs/doc_vision/html/index.html
[vss]: http://www.cbrobotica.org/
[travis]: https://travis-ci.org/SIRLab/VSS-Vision
[sirlab_site]: http://sirlab.github.io/vss.html