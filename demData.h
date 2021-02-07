//
// Created by Frost on 2021/2/6.
//

#ifndef PAPER3_DEMPOST_DEMDATA_H
#define PAPER3_DEMPOST_DEMDATA_H

#include "annulus.h"
#include "cylinder.h"

extern const float pi;

class demData {
private:
    float contactArea;
public:
    int ID;//ID of the particle
    int type;// atom type of the particle
    float radius;
    float mass;
    float u0;// component 1 of the vector speed
    float u1;// component 2 of the vector speed
    float u2;// component 3 of the vector speed
    float f0;// component 1 of the vector force
    float f1;// component 2 of the vector force
    float f2;// component 3 of the vector force
    float x;// component 1 of the vector location
    float y;// component 2 of the vector location
    float z;// component 3 og the vector location

    //calculate the volume of the particle dispersed on a specify range by r1,r2
    //and a particle should not be cut into more than three pieces
    demData(float contactArea = 0,
            int ID = 0,
            int type = 0,
            float radius = 0,
            float mass = 0,
            float u0 = 0,
            float u1 = 0,
            float u2 = 0,
            float f0 = 0,
            float f1 = 0,
            float f2 = 0,
            float x = 0,
            float y = 0,
            float z = 0
            );
    // return the range number, return -1 if the particle isn't in any range
    int classify(annulus* rings, cylinder cylinder1);

    bool isInSphere(float x, float y, float z);


    // return the volume of the sphere part cut by plane
    // sphere cut by cylinder can not be calculated by this function
};


#endif //PAPER3_DEMPOST_DEMDATA_H
