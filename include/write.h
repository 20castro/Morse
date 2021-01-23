// Classe permettant d'écrire dans un fichier wave

#ifndef TAU
#define TAU

static double tau = 6.283185307179586476925286766559;

#endif

#ifndef DEF_WRITE
#define DEF_WRITE

#include <iostream>
#include <fstream>
#include <cmath>

static double amax = 32760; // amplitude maximale

int sine (double, double, int);

class Write{

    public:
        Write (std::ofstream&); // crée le fichier et remplit le header
        ~Write ();

    private:
        void addBytes (long int, int);

    public:
        void addShort ();
        void addLong ();
        void shortSilence ();
        void longSilence ();

    public:
        void addLetter (int); // destiné à recevoir les entiers du dictionnaire de translation

    public:
        void fixHeader (); // rentre la taille réelle du fichier dans le header

    private:
        std::ofstream& file;
        const int rate = 44100; // fréquence d'échantillonage en Hz
        const double unit = 1; // unité de temps en secondes
        const double fshort = 440; // fréquence des "ti" en Hz
};

#endif 