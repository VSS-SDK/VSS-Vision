/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Headers.h"

int main(int argc, char **argv){
	/*
		argv[1] = 0 "imagem", 1 "camera"

		argv[2] = caminho da imagem, id da camera

		argv[3] = 0 ORANGE
				= 1 BLUE
				= 2 RED
				= 3 PINK
				= 4 PURPLE
				= 5 GREEN
				= 6 BROWN
				= 7 ROTATION
				= 8 CUT
				= 9 YELLOW
	*/

	//cout << argc;
	if(argc >= 3){
		Calibration calib;
		stringstream ss;
		string s;
		ss << argv[1];
		s = ss.str();

		//cout << argv[1] << endl;
		//cout << argv[2] << endl;
		//cout << argv[3] << endl;

		if(s == "0"){
			calib.setDevice(false);

			clearSS(ss);
			ss << argv[2];
			s = ss.str();
   			calib.setImagePath(s);

   			int stage;
   			clearSS(ss);
			ss << argv[3];
			ss >> stage;
   			calib.setCalibrationStage(stage);
   			
			//cout << "imagem" << endl;
		}else{
			calib.setDevice(true);

			int id;
			clearSS(ss);
			ss << argv[2];
			ss >> id;
			calib.setID(id);

			int stage;
			clearSS(ss);
			ss << argv[3];
			ss >> stage;
   			calib.setCalibrationStage(stage);

			//cout << "camera" << endl;
		}

		calib.init();
	}
	/*CRUD crud;

	stringstream pathSS;
	pathSS << PATHSAVE << "Laranja.csv";

	VisionColor color;

	color.min.rgb[0] = 13;
	color.min.rgb[1] = 13;
	color.min.rgb[2] = 13;

	color.max.rgb[0] = 100;
	color.max.rgb[1] = 100;
	color.max.rgb[2] = 100;

	//crud.saveVisionColor(pathSS.str(), color);
	crud.loadVisionColor(pathSS.str());*/
}