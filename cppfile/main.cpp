#include <iostream>
#include "../include/build.h"

using namespace std;

int main (){
    cout << "Veuillez entrer un texte à transcrire, un nom de fichier texte (se terminant par l'extension .txt)"
        << " ou un nom de fichier audio (se terminant par une des extensions .wav et .wave)." << endl << ">> ";
    char* title;
    cin >> title;
    recognise (title);
    return 0;
}