/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "CRUD.h"

CRUD::CRUD(){ 

}

vector<string> CRUD::loadStrategies(){
	vector<string> strategies;
	string line;
	read.open("../strategies/strategies");
		while(getline(read, line)){
			strategies.push_back(line);
			//cout << line << endl;
		}
	read.close();

	return strategies;
}


void CRUD::saveVisionColor(string path, VisionColor color){
	write.open(path);
		// Não é necessário usar um for aqui, pois são apenas três variaveis, porém se quiser trocar é uma boa prática
		write << color.min.rgb[0] << ";";
		write << color.min.rgb[1] << ";";
		write << color.min.rgb[2] << endl;

		write << color.max.rgb[0] << ";";
		write << color.max.rgb[1] << ";";
		write << color.max.rgb[2] << endl;
	write.close();
}

void CRUD::saveColor(string path, Pixel color){
	write.open(path);
		// Não é necessário usar um for aqui, pois são apenas três variaveis, porém se quiser trocar é uma boa prática
		write << color.rgb[r] << ";";
		write << color.rgb[g] << ";";
		write << color.rgb[b] << endl;
	write.close();
}

void CRUD::saveRotation(string path, float rotation){
	write.open(path);
		write << rotation << endl;
	write.close();
}

void CRUD::saveCut(string path, Rect cut){
	write.open(path);
		write << cut.tl().x << ";";
		write << cut.tl().y << endl;

		write << cut.br().x << ";";
		write << cut.br().y << endl;
	write.close();
}

void CRUD::saveTeamConfiguration(string path, TeamConfiguration team){
	write.open(path);
		write << team.name << endl;
		for(int i = 0 ; i < 3 ; i++){
			write << team.id[i] << ";";
			write << team.task[i] << ";";
			write << team.color[i] << endl;
		}
		write << team.teamColor << ";" << team.strategy << ";" << team.control << ";" << team.transmission << endl;
	write.close();
}

VisionColor CRUD::loadVisionColor(string path){
	VisionColor visionColor;
	string line;
	string linel;
	stringstream ss;

    read.open(path);
	    getline(read, line);
		ss << line;

		for(int i = 0 ; getline(ss, linel, ';') ; i++){
			visionColor.min.rgb[i] = toInt(linel);
		}

		getline(read, line);
		clearSS(ss);
		ss << line;

		for(int i = 0 ; getline(ss, linel, ';') ; i++){
			visionColor.max.rgb[i] = toInt(linel);
		}
	read.close();

	//visionColor.show();
	return visionColor;
}

Pixel CRUD::loadColor(string path){
	Pixel color;
	string line;
	string linel;
	stringstream ss;
	
	read.open(path);
		getline(read, line);
		ss << line;

		for(int i = 0 ; getline(ss, linel, ';') ; i++){
			color.rgb[i] = toInt(linel);
		}
	read.close();

	//color.show();
	return color;
}

float CRUD::loadRotation(string path){
	float rotation;
	string line;
	stringstream ss;
	
	read.open(path);
		getline(read, line);
		ss << line;

		ss >> rotation;
	read.close();

	return rotation;
}

Rect CRUD::loadCut(string path){
	Rect rect;
	Point top, bottom; 
	string line;
	string linel;
	stringstream ss;

	read.open(path);
	    getline(read, line);
		ss << line;

		getline(ss, linel, ';');
		top.x = toInt(linel);

		getline(ss, linel, ';');
		top.y = toInt(linel);

		getline(read, line);
		clearSS(ss);
		ss << line;

		getline(ss, linel, ';');
		bottom.x = toInt(linel);

		getline(ss, linel, ';');
		bottom.y = toInt(linel);
	read.close();

	//cout << top.x << ", " << top.y << endl;
	//cout << bottom.x << ", " << bottom.y << endl;

	rect = Rect(top, bottom);
	return rect;
}

TeamConfiguration CRUD::loadTeamConfiguration(string path){
	TeamConfiguration teamConf;
	string line;
	string linel;
	stringstream ss;
	
	/*read.open(path);
		getline(read, line);
		ss << line;

		for(int i = 0 ; getline(ss, linel, ';') ; i++){
			color.rgb[i] = toInt(linel);
		}
	read.close();*/

	//teamConf.show();

	return teamConf;
}

