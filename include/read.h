// Classe permettant de lire un fichier wave

#ifndef DEF_READ
#define DEF_READ

#include "wave.h"
#include <cmath>

class Read : public Wavfile{

    public:
        Read (const char*); // ouvre le fichier et extrait les données du header

    public:
        double* fourierMax (double, double, double);
        // approxime une transformation de Fourier sur 0.05 s de son et renvoie son maximum et où il est atteint
        bool harmonique ();
        // à l'aide de Fourier, détremine si l'intensité du son correspond à celle d'un bruit ou pas

    private:
        std::ifstream file;
        int extra; // quantité de données supplémentaires dans le header (par rapport à 44)
        int channels;
        int rate; // fréquence d'échantillonage en Hz
        int sample; // nombre de bits par échantillon
        int longueur; // taille du fichier

        // int* sequence; // ici ou dans une fonction en dehors de la classe ?    
};

#endif