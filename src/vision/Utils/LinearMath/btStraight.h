#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "LinearMath/btVector3.h"

class btStraight{
private:
    float inclination;
    float n;

public:
    float getInclination() { return inclination; }
    float getN() { return n; }
    btVector3 getNormalVector();
    btStraight(){}
    btStraight(btVector3 from, btVector3 to);
    btStraight(btVector3 to);

    void calculateStraight(btVector3 from, btVector3 to);
};

#endif
