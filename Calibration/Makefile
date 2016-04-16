all:
	@echo Compilando Calibration ...
	@g++ -std=c++11 ../Utils/Commons/Commons.cpp ../Utils/CRUD/CRUD.cpp Calibration.cpp Main.cpp -o app `pkg-config --cflags --libs opencv` -o Calibration -w
	./Calibration

clean:
	rm -rf *o Calibration
