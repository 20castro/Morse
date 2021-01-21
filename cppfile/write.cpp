#include "../include/write.h"

int sinus (double aratio, double t, int freq){
    return static_cast <int> (aratio * amax * sin (tau * freq * t));
}

Write::Write (std::ofstream& file) : file (file){
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

Write::~Write (){
    fixHeader ();
    file.close ();
}

void Write::addBytes (long int value, int size){ // en little-endian
    for (; size; --size, value >>= 8){
        file.put (static_cast <char> (value & 0xFF));
    }
}

void Write::addShort (){
    int N = unit*rate, n = 0;
    double r, t;
    for (; n < N; n++){
        r = (double) n / (double) N;
        t = r * (double) unit;
        addBytes (sinus (1. - r, t, fshort), 2); // channel 1
        addBytes (sinus (r, t, fshort), 2); // channel 2
    }
}

void Write::addLong (){
    int q = file.tellp ();
    int N = 2*unit*rate, n = 0;
    double r, t;
    for (; n < N; n++){
        r = (double) n / (double) N;
        t = r * (double) (3*unit);
        addBytes (sinus (1. - r, t, fshort/2), 2); // channel 1
        addBytes (sinus (r, t, fshort/2), 2); // channel 2
    }
}

void Write::shortSilence (){
    for (int N = unit*rate; N; N--){ addBytes (0, 4); } // 0 sur les deux chaînes
}

void Write::longSilence (){
    for (int N = 3*unit*rate; N; N--){ addBytes (0, 4); } // 0 sur les deux chaînes
}

void Write::addLetter (int c){ // si c'est possible, l'argument est c = dict[lettre] sinon on n'appelle pas
    for (; c >> 1; c >>= 1){
        c & 0x01 ? addLong () : addShort ();
        shortSilence ();
    }
    longSilence ();
}

void Write::fixHeader (){
    file.seekp (0, file.end);
    int len = file.tellp ();
    file.seekp (4);
    addBytes (len - 8, 4);
    file.seekp (40);
    addBytes (len - 44, 4);
}
    