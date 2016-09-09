#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


all: vision

vision:
	cd src && make -f Makefile

proto:
	cd src/VSS-Interface/protos && make -f protos.make

run:
	cd src && ./VSS-Vision

docm:
	cd doc && doxygen Doxygen

build_debug:
	cd src && make -f Makefile build_debug

#qt:
	#cd src && qmake -qt=qt5

# ../src/QtOpenCV.h ../src/QtOpenCV.cpp ../src/calibration.h ../src/calibration.cpp ../src/commons.h ../src/commons.cpp ../src/interface.h ../src/interface.cpp ../src/main.cpp ../src/mainwindow.h ../src/mainwindow.cpp ../src/qcustomlabel.h ../src/qcustomlabel.cpp ../src/sqlite.h ../src/sqlite.cpp  ../src/vision.h ../src/vision.cpp ../src/protos/command.pb.h ../src/protos/command.pb.cc ../src/protos/command.proto ../src/protos/state.pb.h ../src/protos/state.pb.cc ../src/protos/state.proto
