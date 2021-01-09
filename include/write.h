// Classe permettant d'écrire dans un fichier wave

#ifndef DEF_WRITE
#define DEF_WRITE

#include "wave.h"
#include <cmath>

static double tau = 6.283185307179586476925286766559;
static double amax = 32760; // amplitude maximale

int sine (double, double, int);
double freq (double, int);

class Write : public Wavfile{

    public:
        Write (const char*); // crée le fichier et remplit le header

    public:
        void addShort ();
        void addLong ();
        void shortSilence ();
        void longSilence ();

    public:
        void addLetter (int); // destiné à recevoir les entiers du dictionnaire de translation

    public:
        void setCur (int);
        void fixHeader (); // rentre la taille réelle du fichier dans le header

    private:
        std::ofstream file;
        const int rate = 44100; // fréquence d'échantillonage en Hz
        const double unit = 0.8; // unité de temps en secondes
        const double fshort = 440; // fréquence des "ti" en Hz
};

#endif 