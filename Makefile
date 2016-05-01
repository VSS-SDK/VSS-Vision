#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


all: vision proto calibration

vision:
	cd src/vision && make -f vision.make

proto:
	cd src/vision && make -f vision.make proto

calibration:
	cd src/calibration && make -f calibration.make

clean:
	cd src/vision && make -f vision.make clean

run:
	cd src/vision && make -f vision.make run
