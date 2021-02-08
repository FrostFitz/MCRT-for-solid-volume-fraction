#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>

#include "./cmake-build-debug/demData.h"
#include "./cmake-build-debug/cylinder.h"
#define precise 15 //specify the precise of the mesh
#define nMCRT 100000
const float pi = 3.1415926535897932;


using namespace std;

int main() {
    // The program is used for calculating solid volume fraction in cylinder!!! only!!
//    // Some data you need to specify at first
//    double diameter = 0.75;
    // create a vector to store the data
    vector<demData> dem;
    demData indem;
    FILE *fp;
    fp = fopen("../all.csv","r");
    if (fp == nullptr)
    {
        perror("Can't open file!!!");
        return -1;
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
                &indem.ID, &indem.type, &indem.radius, &indem.mass, &indem.u0, &indem.u1, &indem.u2,
               &indem.f0, &indem.f1, &indem.f2, &indem.x, &indem.y, &indem.z);
        dem.push_back(indem);
    }//这种读取文件的方法会将最后一行读取两次，因此将最后一行数据弹出。
    fclose(fp);
    dem.pop_back();
    // go through the vector to find maxZ and minZ of the particle centre(Z is flow direction of particles)
    float maxTemp = INT_MIN;
    float minTemp = INT_MAX;
    for (int j = 0; j < dem.size(); ++j) {
         maxTemp = max<float>(maxTemp, dem[j].z);
         minTemp = min<float>(minTemp, dem[j].z);
    }
    cout <<dem.size() << "\t" <<maxTemp << "\t" << minTemp << endl;
    //the maxZ and minZ are the boundary to calculate volume fraction. You can decrease the distance between
    //to see how vf varies with distance
    //specify the centre of x, y of cylinder;
    annulus centre(0,0);

    //mesh the cylinder
    cylinder cylinder1(0.75, (maxTemp- minTemp),precise,centre);
    annulus rings[precise];
    cylinder1.cal(precise, rings);
    // To store the solid volume fraction
    double solidVF[precise] = {0};
    // store the particle number
    int solidNum[precise] = {0};
    vector<demData> count[precise];
    for (auto i : dem) {
        int judge = i.classify(rings, cylinder1);
        if( judge != -1)
            count[judge].push_back(i);
        else
            throw("The particle doesn't belong to any range!!");
    }

    //output particle information
    cout << " ************************ classify information ************************" <<endl;
    for (int k = 0; k < precise; ++k) {
        cout << setw(5) << count[k].size() << " particles are in the range betwenn " <<
        setw(10) << rings[k].r1 <<setw(10) <<" and " <<setw(10)<< rings[k].r2 << endl;
    }
    cout << " ***************** all particles have been classified *****************\n" <<endl;

//     perform monte carlo in every range
    static default_random_engine e((unsigned int)time(nullptr));
    static uniform_real_distribution<float> u(minTemp, maxTemp);
    static default_random_engine e2((unsigned int)time(nullptr));
    static uniform_real_distribution<float> u2(0, 1);
    static default_random_engine e3((unsigned int)time(nullptr));
    static uniform_real_distribution<float> u3(0, 2*pi);
    for (int i = 0; i < precise; ++i) {
        int n = 0;
        for (int k = 0; k < nMCRT; ++k) {

            float z = u(e);

            float r = rings[i].r2 + u2(e2)* (rings[i].r1 - rings[i].r2);

            float theta = u3(e3);
            float x = r*cos(theta);
            float y = r*sin(theta);
//            cout << setw(8) << z << setw(11) << r << setw(11) << theta << endl;
            for(auto j : count[i])
            {
                if (j.isInSphere(x, y, z)) {
                    n++;
                    break;//只要在一个球内就跳出循环，如果生成的点同时在两个球内，就会累加两次了
                }
            }
        }
        solidNum[i] = n;
        solidVF[i] = n/double(nMCRT);
    }

    // output solid volume fraction
    cout << " ****************** solid volume fraction ******************" <<endl;
    for (int l = 0; l < precise; ++l) {
        cout << setw(5) << solidNum[l] << " in " << setw(6)<<nMCRT << setw(8) << solidVF[l] << " in range between " << setw(10) <<rings[l].r1 << setw(10) << rings[l].r2 << endl;
    }
    cout << " ***** saving data to VF.txt *****" << endl;
    ofstream outfile;
    outfile.open("../VF.txt", ofstream::out | ofstream::app);
    for (int i = 0; i < precise; ++i) {
        outfile << setw(10) << (rings[i].r1 + rings[i].r2)/2 << setw(10) << solidVF[i] <<"\r\n";
    }
    cout << " **** data are saved to VF.txt ****" << endl;
    return 0;
}