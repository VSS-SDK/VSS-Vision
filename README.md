# VSS-Vision [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)][gpl3] [![Build Status](https://travis-ci.org/SIRLab/VSS-Vision.svg?branch=master)][travis]

[![Trello Features](https://img.shields.io/badge/Trello-Features-blue.svg)][vss-sdk-features]
[![Trello PBIs](https://img.shields.io/badge/Trello-PBIs-blue.svg)][vss-sdk-pbis]
[![Slack](https://img.shields.io/badge/Slack-Channel-551a8b.svg)][slack]

O VSS-Vision é um sistema de visão computacional open-source que faz parte do VSS-SDK.
Mais informações sobre o framework podem ser encontradas em [VSS-SDK][vss-sdk].


## Installation
```
$ sudo ./configure.sh
$ vss-vision
```

## Development
First Time
```
$ sudo ./configure_with_tests.sh
```

Tests
```
$ cd build
$ make
$ ./tests
```

Execution
```
$ cd build
$ make
$ ./vss-vision
```

## Samples
C++ using the VSS-Interface: [SampleCpp][samplecpp]

## License

This code is licensed under the [GNU GENERAL PUBLIC LICENSE Version 3][gpl3], of which a textual copy is available at [LICENSE.txt](LICENSE.txt).

You are allowed and encouraged to use this software on robotics competitions.  If you do, please let us know.


[vss-sdk]: http://sirlab.github.io/VSS-SDK
[gpl3]: http://www.gnu.org/licenses/gpl-3.0/
[travis]: https://travis-ci.org/SIRLab/VSS-Vision
[install]: https://github.com/SIRLab/VSS-Vision/blob/master/INSTALL.md
[vss-sdk-features]: https://trello.com/b/b4dVV6ug/vss-sdk-features
[vss-sdk-pbis]: https://trello.com/b/m0u389nR/vss-sdk-pbis
[slack]: https://vss-sdk.slack.com
[samplecpp]: https://github.com/SIRLab/VSS-SampleCpp






