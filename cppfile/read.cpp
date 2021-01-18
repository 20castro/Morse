#include "read.h"

Read::Read (const char* nom) : file (nom, std::ios::binary){
    file.seekg (16);
    extra = pickBytes (4) - 16;
    file.seekg (22);
    channels = pickBytes (2);
    file.seekg (24);
    rate = pickBytes (4);
    file.seekg (34);
    sample = pickBytes (2);
    file.seekg (40 + extra);
    longueur = pickBytes (4);
}

double* Read::fourierMax (double inf, double sup, double pas){
    double max [2] = {inf, 0}; 
    double height, sinlevel, coslevel, i;
    for (double f = inf; f <= sup; f += pas){
        height = 0;
        sinlevel = 0;
        coslevel = 0;
        for (int step = 0; step < rate/20; step++){
            i = pickBytes (sample) + pickBytes (sample);
            sinlevel = 40*i*sin (tau*f*step/rate)/rate;
            coslevel = 40*i*cos (tau*f*step/rate)/rate;
        }
        height = sqrt (sinlevel*sinlevel + coslevel*coslevel);
        if (height > max [1]){
            max [0] = f;
            max [1] = height;
        }
    }
    return max;
}

bool Read::harmonique (){
    double* range = fourierMax (20, 2000, 1); // premier passage imprécis
    int level = fourierMax (range [0] - 1, range [0] + 1, 0.01) [1]; // deuxième passage plus étroit et précis
    return level > 2000;
}