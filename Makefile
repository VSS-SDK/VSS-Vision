#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


ifndef VERBOSE
.SILENT:
endif

COMPILER = g++ -std=c++11 -Wall -g
EXEC_PROG = VSS-VISION
BINARIES = $(EXEC_PROG)

SOURCES := $(shell find -name '*.cpp' -not -path "./test/*")

OBJECTS = $(SOURCES:.cpp=.o)

OPENCVLIB = `pkg-config opencv --cflags --libs`
GTKMMLIB = `pkg-config gtkmm-3.0 --cflags --libs`
LIBS = $(OPENCVLIB) $(GTKMMLIB) -lpthread

all: message_compiling $(EXEC_PROG)
	@echo VSS-Vision Build Completed

%.o: %.cpp
	$(COMPILER) -c $(LIBS) -o $@ $< -w

$(EXEC_PROG): $(OBJECTS)
	$(COMPILER) -o $(EXEC_PROG) $(OBJECTS) $(LIBS)

# prevents make from getting confused
.PHONY : run
run:
	./$(EXEC_PROG)

.PHONY : clean 
clean:
	rm -rf $(EXEC_PROG) $(OBJECTS)

.PHONY : proto
proto:
	cd src/VSS-Interface && ./protos.sh

message_compiling:
	@echo Compiling VSS-Vision...
