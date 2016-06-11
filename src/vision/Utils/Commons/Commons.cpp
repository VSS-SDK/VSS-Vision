/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Commons.h"

namespace common{
	void clearSS(stringstream &ss){
		ss.str(string());
        ss.clear();
	}

	float toFloat(string a){
		float aa;
		stringstream ss;
		ss << a;
		ss >> aa;
		return aa; 
	}

	double toDouble(string a){
		double aa;
		stringstream ss;
		ss << a;
		ss >> aa;
		return aa; 
	}

	long long int toLongLongInt(string a){
		long long int aa;
		stringstream ss;
		ss << a;
		ss >> aa;
		return aa; 
	}

	bool toBool(string a){
		string b = "0";
		if(a.compare(b) == 0) return false;
		else return true;
	}

	//! Addendum
	//! --------
	//! 
	string cmdTerminal(string s){
		char buffer[1024];
	    std::string result = "";

	    //! > Get the exit of pipe
	    FILE* pipe = popen(s.c_str(), "r");
	    if (!pipe) return "ERROR";
	    
	    //! > Read all pipe
	    while(!feof(pipe)) {
	    	if(fgets(buffer, 1024, pipe) != NULL)
	    		result += buffer;
	    }

	    pclose(pipe);

	    return result;
	}

	float distance(Point a, Point b){
		return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
	}

	Point midpoint(Point a, Point b){
		return Point(((a.x + b.x) / 2), ((a.y + b.y) / 2));
	}

	//! Addendum
	//! --------
	//! 
	float angulation(Point a, Point b){
		//! > Atan2
		return (atan2(a.y - b.y, a.x - b.x) * (180/CV_PI));
		// TODO: Talvez isso esteja errado
	}

	vss_state::RGB toVSSRGB(Pixel p){
		vss_state::RGB resp;
		
		resp.set_r(p.rgb[0]);
		resp.set_g(p.rgb[1]);
		resp.set_b(p.rgb[2]);

		return resp;
	}
}
