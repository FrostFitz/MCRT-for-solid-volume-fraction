//
// Created by Frost on 2021/2/6.
//

#include "demData.h"

demData::demData(float contactArea, int ID, int type, float radius, float mass, float u0, float u1, float u2,
                 float f0, float f1, float f2, float x, float y, float z) :
                 contactArea(contactArea),ID(ID), type(type), radius(radius), mass(mass), u0(u0), u1(u1),u2(u2),
                 f0(f0), f1(f1), f2(f2), x(x), y(y), z(z)
                 {}

int demData::classify(annulus *rings, cylinder cylinder1) {

    float distance = sqrt(pow((x - cylinder1.getCentre().r1), 2)
            + pow(y - cylinder1.getCentre().r2, 2));
    //judge the range in which centre lays
    int seq = -1;
    for (int i = 0; i < cylinder1.getPrecise(); ++i) {
        if (rings[i].r1 >= distance && rings[i].r2 < distance) {
            seq = i;
        }
    }
    return seq;
}

bool demData::isInSphere(float x, float y, float z) {
    double d = pow(x - this -> x, 2) + pow(y - this -> y, 2) + pow(z - this->z, 2)
              - pow(radius, 2);
    if( d <= 0 )
        return true;
    else
        return false;
}
