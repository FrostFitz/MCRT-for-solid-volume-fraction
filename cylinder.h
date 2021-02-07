//
// Created by Frost on 2021/2/6.
//

#ifndef PAPER3_DEMPOST_CYLINDER_H
#define PAPER3_DEMPOST_CYLINDER_H

#include <iostream>
#include "annulus.h"
#include <cmath>

class cylinder {
private:
    float radius, hight;
    int precise;
    annulus centre;//store x and y of centre of the cylinder
public:
    cylinder(float radius, float hight, int precise = 1, annulus centre = annulus());
    // return the annulus boundary: two double which indicates the distance to centre
    annulus* cal(int precise, annulus* rings);

    int getPrecise();
    inline float getRadius();
    annulus getCentre();
    ~cylinder();
};


#endif //PAPER3_DEMPOST_CYLINDER_H
