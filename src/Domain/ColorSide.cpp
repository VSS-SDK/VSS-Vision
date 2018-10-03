//
// Created by manoel on 01/10/18.
//

#include "Domain/ColorSide.h"

std::string toDescription(ColorSide colorSide){

    switch(colorSide){
        case ColorSide::Right:
            return "Right";
        case ColorSide ::Left:
            return "Left";
        default:
            return "Unknown";
    }

}
