// Classe générale de fichier wave

#ifndef DEF_WAV
#define DEF_WAV

#include <iostream>
#include <fstream>

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