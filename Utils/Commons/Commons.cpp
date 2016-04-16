#include "Commons.h"

namespace common{
	void clearSS(stringstream &ss){
		ss.str(string());
        ss.clear();
	}

	string toString(int a){
		stringstream ss;
		ss << a;
		return ss.str();
	}

	string toString(float a){
		stringstream ss;
		ss << a;
		return ss.str();
	}

	string toString(double a){
		stringstream ss;
		ss << a;
		return ss.str();
	}

	string toString(long long int a){
		stringstream ss;
		ss << a;
		return ss.str();
	}

	string toString(bool a){
		string s;
		if(a) s = "1";
		else s = "0";
		return s;
	}

	int toInt(char a){
		int aa;
		stringstream ss;
		ss << a;
		ss >> aa;
		return aa; 
	}

	int toInt(string a){
		int aa;
		stringstream ss;
		ss << a;
		ss >> aa;
		return aa; 
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

	string cmdTerminal(string s){
		char buffer[1024];
	    std::string result = "";

	    FILE* pipe = popen(s.c_str(), "r");
	    if (!pipe) return "ERROR";
	    
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

	float angulation(Point a, Point b){
		return (atan2(a.y - b.y, a.x - b.x) * (180/CV_PI));
		// TODO: Talvez isso esteja errado
	}
}
