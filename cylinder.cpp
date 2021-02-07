//
// Created by Frost on 2021/2/6.
//

#include "cylinder.h"

cylinder::cylinder(float radius, float hight, int precise, annulus centre) :
        radius(radius), hight(hight), precise(precise), centre(centre){
}

annulus* cylinder::cal(int precise, annulus* rings) {
    if (precise < 0)
        std::cout << "Precise cann't be less than 0.\n\tPlease STOP!!!" << std::endl;
    float deltaR = radius/precise;
    for (int i = 0; i < precise; ++i) {
        rings[i] = annulus(radius - i * deltaR, radius - (i+1)*deltaR);
    }
    return rings;
}

int cylinder::getPrecise() {
    return precise;
}

inline float cylinder::getRadius() {
    return radius;
}

annulus cylinder::getCentre() {
    return centre;
}

cylinder::~cylinder() {
}
