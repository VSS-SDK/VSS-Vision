/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "common.h"

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
        QProcess process;
        process.start(s.c_str());
        process.waitForFinished(-1); // will wait forever until finished

        QString stdout = process.readAllStandardOutput();
        string result = stdout.toUtf8().constData();
        return result;
    }

    double distancePoint(btVector3 a, btVector3 b){
        return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
    }

    double distancePoint(Point a, Point b){
        return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
    }

    Point midpoint(Point a, Point b){
        return Point(((a.x + b.x) / 2.0), ((a.y + b.y) / 2.0));
    }

    Point midpoint(Rect testLabel){
        return Point(testLabel.x + (testLabel.width/2.0), testLabel.y  + (testLabel.height/2.0));
    }

    float angulation(Point a, Point b){
        return (atan2(a.y - b.y, a.x - b.x) * (180/CV_PI));
    }

    double radian(Point a, Point b){
        return atan2(a.y - b.y, a.x - b.x);
    }
}
