#ifndef CRUD_H_
#define CRUD_H_

#include "../Commons/Commons.h"
#include "string"
#include "fstream"

using namespace common;

class CRUD{
private:
	ofstream write;
	ifstream read;

public:
	CRUD();

	void clearAll();
	vector<string> loadStrategies();

	void saveVisionColor(string path, VisionColor);
	void saveColor(string path, Pixel);
	void saveRotation(string path, float);
	void saveCut(string path, Rect cut);
	void saveTeamConfiguration(string path, TeamConfiguration);
	
	VisionColor loadVisionColor(string path);
	Pixel loadColor(string path);
	float loadRotation(string path);
	Rect loadCut(string path);	
	TeamConfiguration loadTeamConfiguration(string path);
};

#endif
