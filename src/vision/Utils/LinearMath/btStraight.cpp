#include "LinearMath/btStraight.h"

btStraight::btStraight(btVector3 from, btVector3 to){
    calculateStraight(from,to);
}

btStraight::btStraight(btVector3 to){
    btStraight(btVector3(0,0,0),to);
}

void btStraight::calculateStraight(btVector3 from, btVector3 to){
    btVector3 relVec = to - from;
    inclination = relVec.getZ()/relVec.getX();

    n = to.getZ() - inclination*to.getX();
}

btVector3 btStraight::getNormalVector(){
    float xComp = cos(atan(getInclination()));
    float zComp = xComp*getInclination();

    return btVector3(xComp,0,zComp);
}

