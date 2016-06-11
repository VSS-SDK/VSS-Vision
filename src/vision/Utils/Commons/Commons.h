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
#include "../LinearMath/btVector3.h"
#include "../interface/interface.h"

using namespace std;
using namespace cv;

//! This namespace is responsible to implement all global functions and custom datatypes used in the software, like: ENUMS, Pixel, VisionColor, glRigidBody, TeamConfiguration.
namespace common{
	//! This enum implements a abstraction of a RGB array.
	enum{ r = 0, g = 1, b = 2 };

	//! This enum implements a abstraction of a HSV array.
	enum{ h = 0, s = 1, v = 2 };

	//! This enum implements a state machine, this is responsible for represent all states that a subprocess can tue. 
	enum{ STOPPED = 0, STARTING = 1, RUNNING = 2, PAUSING = 3, PAUSED = 4, ENDING = 5, FINISHED = 6, CRASHED = -1 };

	//! This enum implements a abstraction of teams.
	enum{ OUR_TEAM = 0, ADVERSARY_TEAM = 1 };

	//! This enum implements all cameras that the software can tue.
	enum{ TOP = 0, TV1 = 1, TV2 = 2, BACK = 3, FRONT = 4, TEAM1 = 5, TEAM2 = 6, TEAM3 = 7, ADV1 = 8, ADV2 = 9, ADV3 = 10, BALL = 11 };
	
	//! This enum represents all data that can be calibrated.
	enum{ ORANGE = 0, BLUE = 1, RED = 2, PINK = 3, PURPLE = 4, GREEN = 5, BROWN = 6, YELLOW = 7, ROTATION = 8, CUT = 9 };

	// Visão TODO: descrever o que é isso
	enum{ V_BALL = 0, V_OUR_TEAM = 1, V_ADVERSARY_TEAM = 2, V_SIR1 = 3, V_SIR2 = 4, V_SIR3 = 5 };

	//! This enum implements a abstraction of direction wheel on robots.
	enum{ LEFT = 0, RIGHT = 1 };

	//! This enum implements some kinds of errors.
	enum{ UNKNOWN = -1, KNOWN = 1, NONE = 0 };	// TODO: retirar isso

	//! This struct represents a Pixel, can be: RGB and HSV. It's used float because is possible to represent color in systems, like: 0 to 1, and 0 to 255.
	struct Pixel{
		//! Data: array[3] of RGB.
	    float rgb[3]; 

	    //! Constructor default: Pixel p;
	    Pixel(){
	    	rgb[0] = 0;
	    	rgb[1] = 0;
	    	rgb[2] = 0;
	    };

	    //! Constructor RGB1: Pixel p(r, g, b);
	    Pixel(float r, float g, float b){
	        rgb[0] = r;
	        rgb[1] = g;
	        rgb[2] = b;
	    };

	    //! Constructor RGB2: Pixel p(rgb[3]);
	    Pixel(float rgb[3]){
	        for(int i = 0 ; i < 3 ; i++){
	            this->rgb[i] = rgb[i];
	        }
	    };

	    //! Constructor copy: Pixel p(Pixel(r, g, b));
	    Pixel(Pixel *p){
	        for(int i = 0 ; i < 3 ; i++){
	            rgb[i] = p->rgb[i];
	        }
	    };

	    //! Constructor btVector3: Pixel p(btVector(r, g, b));
	    Pixel(btVector3 *p){
	    	rgb[0] = p->getX();
	    	rgb[1] = p->getY();
	    	rgb[2] = p->getZ();
	    };

	    //! Default function: prints all variables.
	    void show(){
	    	printf("Pixel(%.2f, %.2f, %.2f)\n", rgb[0], rgb[1], rgb[2]);
	    };
	};

	//! This struct represents a Color that can be calibrated: made by 2 Pixels that represents a range of color, Bottom Pixel Limit and Top Pixel Limit.
	struct VisionColor{
		//! Bottom Pixel Limit
		Pixel min;
		//! Top Pixel Limit
		Pixel max;

		//! Constructor default: VisionColor c;
		VisionColor(){
			min = Pixel(0, 0, 0);
			max = Pixel(255, 255, 255);
		};

		//! Constructor Pixels: VisionColor c( Pixel (r, g, b), Pixel (r, g, b));
		VisionColor(Pixel min, Pixel max){
			this->min = min;
			this->max = max;
		};

		//! Constructor copy: VisionColor c( VisionColor );
		VisionColor(VisionColor *color){
			min = color->min;
			max = color->max;
		};

		//! Default function: prints all variables.
		void show(){
			printf("VisionColor\nMin");
			min.show();
			printf("Max");
			max.show();
		}
	};

	//! This struct represents a RigidBody, see: [RigidBody](https://en.wikipedia.org/wiki/Rigid_body). Position, orientation, scale and color.
	struct glRigidBody{
		//! Position in R^3
		btVector3 position;
		//! Orientation in R^3
		btVector3 orientation;
		//! Scale in R^3
		btVector3 scale;
		//! Color of body
		Pixel color;

		//! Constructor default: glRigidBody rb;
		glRigidBody(){
			position = btVector3(0, 0, 0);
			orientation = btVector3(0, 0, 0);
			scale = btVector3(1, 1, 1);
			color = Pixel(0, 0, 0);
		};

		//! Method responsible for set a new position.
		void setPosition(btVector3 p){
			position = p;
		};

		//! Method responsible for set a new orientation.
		void setOrientation(btVector3 p){
			orientation = p;
		};

		//! Method responsible for set a new scale.
		void setScale(btVector3 p){
			scale = p;
		};

		//! Method responsible for set a new color.
		void setColor(Pixel p){
			color = p;
		}

		//! Default function: prints all variables.
		void show(){
			cout << "glRigidBody" << endl;
			cout << " ------ " << endl;
			cout << "position" << endl;
			position.show();
			cout << "orientation" << endl;
			orientation.show();
			cout << "scale" << endl;
			scale.show();
			cout << "color" << endl;
			color.show();
		}
	};

	//! This struct represents a Configuration that a team can save and load.
	struct TeamConfiguration{
		//! Name of configuration, example: BOOOOOORA_HORA_DO_SHOW_P****_2015
		string name;
		//! Id of robots
		int id[3];
		//! Task of each robot
		int task[3];
		//! Color of each robot: Enum color; (DEPRECATED)
		int color[3];
		//! Color of team: Enum color;
		int teamColor;
		//! Strategy: (DEPRECATED)
		int strategy;
		//! Control: (DEPRECATED)
		int control;
		//! Transmission: (DEPRECATED)
		int transmission;

		//! Constructor default: TeamConfiguration tf;
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

		//! Constructor copy: TeamConfiguration new( TeamConfiguration old );
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

		//! Default function: prints all variables.
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

	//! Method responsible for clean a stringstream variable.
	void clearSS(stringstream &ss);

	//! Method responsible for convert all simple datatypes to string;
	template <typename T>
	string toString (T parameter){
		stringstream ss;
		ss << parameter;
		return ss.str();
	}
	
	//! Method responsible for convert all simple datatypes to int.
	template <typename T>
	int toInt (T parameter){
		int aa;
		stringstream ss;
		ss << parameter;
		ss >> aa;
		return aa; 
	}
	
	//! Method responsible for convert string to float;
	float toFloat(string a);
	
	//! Method responsible for convert string to double;
	double toDouble(string a);

	//! Method responsible for convert string to long long int;
	long long int toLongLongInt(string a);

	//! Method responsible for convert string to bool;
	bool toBool(string a);

	//! Method responsible for access the Terminal and get the exit of data.
	string cmdTerminal(string s);

	//! Method responsible for calculate the distance between two points (btVector3) R^3
	float distance(btVector3, btVector3);

	//! Method responsible for calculate the distance between two points (Point) R^2
	float distance(Point, Point);

	//! Method responsible for calculate the midpoint between two points (btVector3) R^3
	btVector3 midpoint(btVector3, btVector3);

	//! Method responsible for calculate the midpoint between two points (Point) R^2
	Point midpoint(Point, Point);

	//! Method responsible for calculate the angulation between two points (Point) R^2
	float angulation(Point, Point);

	//! Method responsible for convert Pixel to vss_state::RGB.
	vss_state::RGB toVSSRGB(Pixel);
}

#endif	