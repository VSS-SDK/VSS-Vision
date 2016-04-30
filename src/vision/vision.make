#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


CCX = g++ -std=c++11 -w



INCLUDES = -I -ICalibration -IUtils -IUtils/CRUD -IUtils/Commons -IUtils/Draw -IUtils/Imgui -IUtils/interface

LIBRARIES_OPENCV = -lopencv_calib3d -lopencv_contrib -lopencv_objdetect -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml 
LIBRARIES_OPENCV += -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videoio -lopencv_imgcodecs -lopencv_videostab
LIBRARIES_GLFW = `pkg-config --static --libs glfw3` -lGLU -lglut -lGL -lX11 -lXxf86vm -lXrandr -lXi
LIBRARIES_PROTO = `pkg-config --cflags --libs protobuf`

LIBRARIES = $(LIBRARIES_OPENCV) $(LIBRARIES_PROTO) $(LIBRARIES_GLFW) -lzmq  -pthread -lm -w



SRC := $(shell find -name '*.cpp')
FILE_NAMES_SRC = $(SRC:.cpp=.o)

PROTOS := $(shell find -name '*.cc')
FILE_NAMES_PROTOS = $(PROTOS:.cc=.o)

FILE_NAMES = $(FILE_NAMES_SRC) $(FILE_NAMES_PROTOS) 



EXEC = VSS-Vision

.cpp.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -c -o $@ $< -w

.cc.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -c -o $@ $< -w

all: message_compiling $(EXEC)
	@echo Done ...
	
message_compiling:
	@echo Compiling VSS-Vision ...

message_cleaning:
	@echo Cleaning VSS-Vision ...

run:
	./MPP

$(EXEC): proto $(FILE_NAMES)
	@$(CCX) -o $(EXEC) $(FILE_NAMES) $(LIBRARIES) $(INCLUDES)

clean: message_cleaning
	@rm $(EXEC) $(FILE_NAMES)

proto:
	cd Utils/interface/protos && make -f protos.make

teste: 
	$(SRC)
