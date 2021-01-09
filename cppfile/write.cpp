#include "write.h"

int sinus (double aratio, double t, int freq){
    return static_cast <int> (aratio * amax * sin (tau * freq * t));
}

double freq (double fbase, int t){
    double T = 4*44100*60; // nombre de bits pour coder 1' de son
    double ev = exp ((double) t / T);
    return fbase * (1. + 0.3*ev);
}

Write::Write (const char* nom) : file (nom, std::ios::binary){
    file << "RIFF----WAVEfmt "; // les tirets seront complétés par fixHeader (taille du fichier, sur 4 octets)
    addBytes (16, 4);
    addBytes (1, 2);
    addBytes (2, 2);
    addBytes (44100, 4);
    addBytes (44100*2*2, 4);
    addBytes (4, 2);
    addBytes (16, 2);
    file << "data----"; // les tirets seront complétés par fixHeader (taille de la partie data, sur 4 octets)
}

void Write::addShort (){
    int N = unit*rate, n = 0;
    double r, t;
    for (; n < N; n++){
        r = (double) n / (double) N;
        t = r / (double) rate;
        addBytes (sinus (1. - r, t, fshort), 2); // channel 1
        addBytes (sinus (r, t, fshort), 2); // channel 2
    }
}

void Write::addLong (){
    int q = file.tellp ();
    double flong = freq (fshort, q - 44);
    // fréquence des "ta" (légèrement supérieure au début puis se rapproche de fshort en 1' environ)
    int N = 2*unit*rate, n = 0; // 2 (et non 3) car on ajoute déjà un silence court (de 1) après chaque lettre
    double r, t;
    for (; n < N; n++){
        r = (double) n / (double) N;
        t = r / (double) rate;
        addBytes (sinus (1. - r, t, flong), 2); // channel 1
        addBytes (sinus (r, t, flong), 2); // channel 2
    }
}

void Write::shortSilence (){
    for (int N = unit*rate; N; N--){ addBytes (0, 4); } // 0 sur les deux chaînes
}

void Write::longSilence (){
    for (int N = 3*unit*rate; N; N--){ addBytes (0, 4); } // 0 sur les deux chaînes
}

void Write::addLetter (int c){ // si c'est possible, l'argument est c = dict[lettre] sinon on n'appelle pas
    if (c){
        for (; c >> 1; c >>= 1){ c & 1 ? addLong () : addShort (); }
        shortSilence ();
    }
    else{ longSilence (); }
}

void Write::setCur (int cur){
    file.seekp (cur);
}

void Write::fixHeader (){
    file.seekp (0, file.end);
    int len = file.tellp ();
    file.seekp (4);
    addBytes (len - 8, 4);
    file.seekp (40);
    addBytes (len - 44, 4); // bien 44 ?
}