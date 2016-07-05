#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


all: vision proto

vision:
	cd src && make -f Makefile

proto:
	cd src/protos && make -f protos.make

run:
	cd src && ./VSS-Vision

qt:
	cd src && qmake -qt=qt5

