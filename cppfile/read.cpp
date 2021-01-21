#include "../include/read.h"

double max (std::vector <double> u){
    double maximum = u [0];
    const int L = u.size ();
    for (double x : u){
        if (x > maximum){ maximum = x; }
    }
    return maximum;
}

Read::Read (std::ifstream& file) : file (file){
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

Read::~Read (){
    file.close ();
}

int Read::pickBytes (int size){ // en little-endian
    int res = 0;
    int pow = 1;
    for (; size; size--, pow *= 256){
        res += pow*file.get ();
    }
    return res;
}

std::vector <double> Read::fourierMax (double inf, double sup, double pas, bool stayThere = false){
    const int there = file.tellg ();
    std::vector <double> maxi (2);
    maxi [0] = inf;
    maxi [1] = 0;
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
        if (height > maxi [1]){
            maxi [0] = f;
            maxi [1] = height;
        }
    }
    if (stayThere){ file.seekg (there); }
    return maxi;
}

bool Read::harmonique (){
    std::vector <double> range = fourierMax (20, 2000, 1, true);
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