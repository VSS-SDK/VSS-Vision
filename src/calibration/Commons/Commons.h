/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef COMMONS_H_
#define COMMONS_H_

#include "iostream"
#include <opencv2/highgui/highgui.hpp>	// Visão Computacional
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/videoio.hpp"
#include "../../vision/Utils/LinearMath/btVector3.h"

using namespace std;
using namespace cv;

namespace common{
	enum{ r = 0, g = 1, b = 2 };
	enum{ h = 0, s = 1, v = 2 };

	/*
		Estados pelo qual um processo pode estar passando (Máquina Simples de Estados)

		STOPPED (Estado de não iniciado)
			* STOPPED -> STARTING
			* STOPPED -> PAUSING
			* STOPPED -> CRASHED

		STARTING (Estado de iniciando)
			* STARTING -> RUNNING
			* STARTING -> PAUSING
			* STARTING -> ENDING
			* STARTING -> CRASHED

		RUNNING (Estado de rodando)
			* RUNNING -> PAUSING
			* RUNNING -> ENDING
			* RUNNING -> CRASHED

		PAUSING (Estado de iniciando uma pausa)
			* PAUSING -> PAUSED
			* PAUSING -> CRASHED

		PAUSED (Estado de pausado)
			* PAUSED -> STARTING
			* PAUSED -> ENDING
			* PAUSED -> CRASHED

		ENDING (Estado de terminando)
			* ENDING -> FINISHED
			* ENDING -> CRASHED

		FINISHED (Estado de terminado)
			* FINISHED -> STOPPED
			* FINISHED -> CRASHED
	*/
	enum{ STOPPED = 0, STARTING = 1, RUNNING = 2, PAUSING = 3, PAUSED = 4, ENDING = 5, FINISHED = 6, CRASHED = -1 };

	// Tipos de papéis que podem ser empregados
	enum{ FORWARD_GOALKEEPER = 0, BACKWARD_GOALKEEPER = 1, FORWARD_DEFENDER = 2, BACKWARD_DEFENDER = 3, FORWARD_ATTACKER = 4, BACKWARD_ATTACKER = 5, UNKNOWN = -1 };

	// Times
	enum{ OUR_TEAM = 0, ADVERSARY_TEAM = 1 };

	// Tipos de Camera
	enum{ TOP = 0, TV1 = 1, TV2 = 2, BACK = 3, FRONT = 4, TEAM1 = 5, TEAM2 = 6, TEAM3 = 7, ADV1 = 8, ADV2 = 9, ADV3 = 10, BALL = 11 };
	
	// Possiveis coisas para se calibrar na visão computacional
	enum{ ORANGE = 0, BLUE = 1, RED = 2, PINK = 3, PURPLE = 4, GREEN = 5, BROWN = 6, YELLOW = 7, ROTATION = 8, CUT = 9 };

	// Possiveis processos principais a serem executados
	enum{ VSS = 0, SIMULATOR = 1, VSS_SIMULATOR = 2, NONE = -1 };

	// Visão TODO: descrever o que é isso
	enum{ V_BALL = 0, V_OUR_TEAM = 1, V_ADVERSARY_TEAM = 2, V_SIR1 = 3, V_SIR2 = 4, V_SIR3 = 5 };

	// Roda de um robô
	enum{ LEFT = 0, RIGHT = 1 };

	struct Pixel{
	    float rgb[3];  
	    Pixel(){
	    	rgb[0] = 0;
	    	rgb[1] = 0;
	    	rgb[2] = 0;
	    };
	    Pixel(float r, float g, float b){
	        rgb[0] = r;
	        rgb[1] = g;
	        rgb[2] = b;
	    };
	    Pixel(float rgb[3]){
	        for(int i = 0 ; i < 3 ; i++){
	            this->rgb[i] = rgb[i];
	        }
	    };
	    Pixel(Pixel *p){
	        for(int i = 0 ; i < 3 ; i++){
	            rgb[i] = p->rgb[i];
	        }
	    };
	    Pixel(btVector3 *p){
	    	rgb[0] = p->getX();
	    	rgb[1] = p->getY();
	    	rgb[2] = p->getZ();
	    };
	    void show(){
	    	printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
	    };
	};

	struct TeamConfiguration{
		string name;
		int id[3];
		int task[3];
		int color[3];
		int teamColor;
		int strategy;
		int control;
		int transmission;

		TeamConfiguration(){
			for(int i = 0 ; i < 3 ; i++){
				id[i] = i;
				task[i] = UNKNOWN;
				color[i] = UNKNOWN;
			}

			teamColor = UNKNOWN;
			strategy = 0;
			control = 0;
			transmission = 0;
		};
		TeamConfiguration(TeamConfiguration *g){
			for(int i = 0 ; i < 3 ; i++){
				id[i] = g->id[i];
				task[i] = g->task[i];
				color[i] = g->color[i];	
			}

			teamColor = g->teamColor;
			strategy = g->strategy;
			control = g->control;
			transmission = g->transmission;
		};
		void show(){
			printf("TeamConfiguration:\n");
			for(int i = 0 ; i < 3 ; i++){
				printf("Robot %d(%d, %d, %d)\n", i+1, id[i], task[i], color[i]);
			}
			printf("Color %d\n", teamColor);
			printf("Strategy %d\n", strategy);
			printf("Control %d\n", control);
			printf("Transmission %d\n", transmission);
		}
	};

	struct VisionColor{
		Pixel min;
		Pixel max;

		VisionColor(){
			min = Pixel(0, 0, 0);
			max = Pixel(255, 255, 255);
		};
		VisionColor(Pixel min, Pixel max){
			this->min = min;
			this->max = max;
		};
		VisionColor(VisionColor *color){
			min = color->min;
			max = color->max;
		};
		void show(){
			printf("VisionColor\nMin");
			min.show();
			printf("Max");
			max.show();
		}
	};

	void clearSS(stringstream &ss);

	template <typename T>
	string toString (T parameter){
		stringstream ss;
		ss << parameter;
		return ss.str();
	}
	
	template <typename T>
	int toInt (T parameter){
		int aa;
		stringstream ss;
		ss << parameter;
		ss >> aa;
		return aa; 
	}
	
	float toFloat(string a);
	double toDouble(string a);
	long long int toLongLongInt(string a);
	bool toBool(string a);

	string cmdTerminal(string s);

	float distance(btVector3, btVector3);
	float distance(Point, Point);

	Point midpoint(Point, Point);
	btVector3 midpoint(btVector3, btVector3);

	float angulation(Point, Point);
}

#endif	