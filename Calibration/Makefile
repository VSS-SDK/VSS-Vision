#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#

all:
	@echo Compilando Calibration ...
	@g++ -std=c++11 ../Utils/Commons/Commons.cpp ../Utils/CRUD/CRUD.cpp Calibration.cpp Main.cpp -o app `pkg-config --cflags --libs opencv` -o Calibration -w
	./Calibration

clean:
	rm -rf *o Calibration
