#
# This file is part of the VSS-Vision project.
#
# This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
# v. 3.0. If a copy of the GPL was not distributed with this
# file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
#


CXX = g++ -std=c++11 -w

EXE = VSS-Vision
OBJS = Main.o GUI.o Robot.o Core.o Vision.o
OBJS += Utils/Imgui/imgui_impl_glfw.o Utils/Draw/Draw.o Utils/CRUD/CRUD.o Utils/Zocket/Zocket.o Utils/Zocket/Protos/sirlab.pb.o
OBJS += Utils/Imgui/imgui.o Utils/Imgui/imgui_draw.o Utils/Commons/Commons.o Utils/Imgui/imgui_demo.o

UNAME_S := $(shell uname -s)


ECHO_MESSAGE = "Linux"
LIBS = `pkg-config --static --libs glfw3` -lopencv_calib3d -lopencv_contrib -lopencv_objdetect -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab `pkg-config --cflags --libs protobuf` -w -lzmq -lGLU -lglut -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi


CXXFLAGS = -I../../ `pkg-config --cflags glfw3` -lopencv_calib3d -lopencv_contrib -lopencv_objdetect -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab `pkg-config --cflags --libs protobuf`  -w
CXXFLAGS += -Wall -Wformat
CFLAGS = $(CXXFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $< -w

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

run:
	./VSS-Vision

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

clean:
	rm $(EXE) $(OBJS)

