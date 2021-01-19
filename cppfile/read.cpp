#include "read.h"

double max (std::vector <double> u){
    double max = u [0];
    for (std::vector <double>::iterator it; it != u.end (); it++){
        if (*it > max){ max = *it; }
    }
    return max;
}

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

double* Read::fourierMax (double inf, double sup, double pas, bool stayThere = false){
    const int there = file.tellg ();
    double max [2] = {inf, 0}; 
    double height, sinlevel, coslevel, i;
    for (double f = inf; f <= sup; f += pas){
        sinlevel = 0;
        coslevel = 0;
        for (int step = 0; step < rate/10; step++){
            i = 0;
            for (int k = 0; k < channels; k++){ i += pickBytes (sample); }
            sinlevel += 20*i*sin (tau*f*step/rate)/rate;
            coslevel += 20*i*cos (tau*f*step/rate)/rate;
        }
        height = sqrt (sinlevel*sinlevel + coslevel*coslevel);
        if (height > max [1]){
            max [0] = f;
            max [1] = height;
        }
    }
    if (stayThere){ file.seekg (there); }
    return max;
}

bool Read::harmonique (){
    double* range = fourierMax (20, 2000, 1, true);
    // premier passage imprécis
    int level = fourierMax (range [0] - 1, range [0] + 1, 0.01, false) [1];
    // deuxième passage plus étroit et précis
    return level > 2000;
}

std::vector <double> Read::fill (){
    int cnt = 0;
    double val = 0;
    bool state = false, newstate;
    const int L = (10*longueur)/(channels*sample*rate);
    std::vector <double> sequence;
    for (int step = 0; step < L; step++){
        newstate = harmonique ();
        if (state xor newstate){
            if (cnt){ sequence.push_back (val); }
            // on ignore toujours le silence qu'il y a au début (même s'il est nul)
            state = newstate;
            cnt++;
            val = 0;
        }
        val += 0.1;
    }
    sequence.push_back (val);
    cnt++;
    sequence.resize (cnt);
    return sequence;
}