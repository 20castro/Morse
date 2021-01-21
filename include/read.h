// Classe permettant de lire un fichier wave

#ifndef TAU
#define TAU

static double tau = 6.283185307179586476925286766559;

#endif

#ifndef DEF_READ
#define DEF_READ

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

double max (std::vector <double>);

class Read{

    public:
        Read (std::ifstream&); // ouvre le fichier et extrait les données du header
        ~Read ();

    private:
        int pickBytes (int);

    public:
        std::vector <double> fourierMax (double, double, double, bool);
        // approxime une transformation de Fourier sur 0.1 s de son et renvoie son maximum et où il est atteint
        bool harmonique ();
        // à l'aide de Fourier, détremine si l'intensité du son correspond à celle d'un bruit ou pas
        std::vector <double> fill ();

    private:
        std::ifstream& file;
        int extra; // quantité de données supplémentaires dans le header (par rapport à 44)
        int channels;
        int rate; // fréquence d'échantillonage en Hz
        int sample; // nombre de bits par échantillon
        int longueur; // taille du fichier
};

#endif