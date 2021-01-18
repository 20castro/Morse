// Classe générale de fichier wave

#ifndef DEF_WAV
#define DEF_WAV

#include <iostream>
#include <fstream>

static double tau = 6.283185307179586476925286766559;

class Wavfile{

    public:
        void addBytes (int, int);
        int pickBytes (int);

    public:
        void closeFile ();

    private:
        std::fstream file;
};

#endif