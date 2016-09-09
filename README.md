VSS-Vision 
==========
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)][gpl3]
[![Build Status](https://travis-ci.org/SIRLab/VSS-Vision.svg?branch=master)][travis]
[![Link: Youtube](https://img.shields.io/badge/Link-Youtube-red.svg)][youtube]


O VSS-Vision é uma das partes de um framework que está sendo desenvolvido para a categoria de futebol de robôs [IEEE Very Small Size Soccer (VSSS)][vss], que consiste em:

> Um programa de Visão Computacional global para a categoria, o [VSS-Vision][vss-vision];

> Um simulador para a categoria, o [VSS-Simulator][vss-simulator];

> Um visualizador de estados em 3D para categoria, o [VSS-Viewer][vss-viewer];

> Uma base de estratégia que pode ser utilizada para obter e enviar dados dos três projetos citados, o [VSS-SampleStrategy][vss-sample].

Mais informações sobre o framework podem ser encontradas em [sirlab.github.io][sirlab_site].


VSS-Vision Wiki
---------------
[WIKI][wiki]

Documentation
-------------
[Doxygen][doxygen]

Installation
------------
[INSTALL][install]

Cloning
-------
```
$ git clone --recursive https://github.com/SIRLab/VSS-Vision.git
```

Development and Use
-------------------
```
$ cd VSS-Vision
$ make proto
$ make
$ make run
```


Gallery
-------
![screenshot 1](https://raw.githubusercontent.com/SIRLab/VSS-Vision/master/images/top2.png)

![screenshot 2](https://raw.githubusercontent.com/SIRLab/VSS-Vision/master/images/top.png)


DOING
-----
* Re-Adicionar o salvamento de calibragens ao sistema

TODO	
----
* Adicionar filtro de kalman no algoritmo de visão
* Adicionar otimização de secção no algoritmo de visão



License
-------

This code is licensed under the [GNU GENERAL PUBLIC LICENSE Version 3][gpl3], of which a textual copy is available at [LICENSE.txt](LICENSE.txt).

You are allowed and encouraged to use this software on the IEEE Very Small Size Soccer competitions.  If you do, please let us know.

[sirface]: https://www.facebook.com/sirlab.faeterj/
[siryou]: https://www.youtube.com/channel/UCLXQhza5oA2EJYsYDbr41ZQ
[sirlink]: https://www.linkedin.com/company/sir-lab
[sirlab_site]: http://sirlab.github.io/vss.html

[vss-vision]: https://github.com/SIRLab/VSS-Vision
[vss-simulator]: https://github.com/SIRLab/VSS-Simulator
[vss-viewer]: https://github.com/SIRLab/VSS-Viewer
[vss-sample]: https://github.com/SIRLab/VSS-SampleStrategy

[gpl3]: http://www.gnu.org/licenses/gpl-3.0/
[vss]: http://www.cbrobotica.org/
[travis]: https://travis-ci.org/SIRLab/VSS-Vision

[install]: https://github.com/SIRLab/VSS-Vision/blob/master/INSTALL.md
[wiki]: https://github.com/SIRLab/VSS-Vision/wiki
[doxygen]: http://sirlab.github.io/VSS-Vision
[youtube]: https://www.youtube.com/watch?v=LnWzAgE9Oqs







