#include "build.h"

void toMorse (const char* text){
    std::map <char, int> dict = buildMap ();
    Write w ("transcription.wav");
    for (int j = 0; text [j]; j++){
        if (dict.find (letterCast (text [j])) != dict.end ()){
            w.addLetter (dict[text[j]]);
        }
        else{
            // Si le caractère n'est pas dans le dictionnaire, on l'ignore
        }
    }
    w.fixHeader ();
    w.closeFile ();
}

void fromMorse (const char* title){
    Read r (title); // fichier audio à lire
    std::vector <double> sequence = r.fill ();
    double unit = max (sequence)/3; // longueur d'un point
    // dans la suite, ce qui nous intéresse sera alors uniquement le vecteur sequence (on peut supprimer r)
    // dans sequence, le son est aux indices pairs et les silences aux indices impairs
    r.closeFile (); // devrait pouvoir s'intégrer au delete
    delete &r;
    std::ofstream f ("transcription.txt"); // fichier qui va contenir la transcription
    
    /* corps (traitement de sequence, ie on construit l'arbre et on le parcourt jusqu'à tomber sur un silence
    long : à ce moment, on ajoute la lettre correspondante à f avec << puis un espace ou jusqu'à tomber sur
    la dernière case du vecteur : à ce moment, on ajoute juste la lettre) */

    f.close ();
}

bool ending (const char* title, const char* ext, const int ltitle, const int lext){
    // les deux derniers arguments sont des tailles de chaînes de caractères (sans compter le caractère final)
    bool res = true;
    for (int k = 0; res and k < lext; res = (title [ltitle - 1 - k] == ext [lext - 1 - k]), k++){}
    return res;
}

void recognise (const char* title){
    int len = 0;
    bool flag = true;
    for (; title [len] and flag; flag = len < 64, len++){}
    // on estime qu'un nom de document fait au plus 64 caractères
    if (flag and (ending (title, ".wav", len, 4) or ending (title, ".wave", len, 5))){
        fromMorse (title);
        std::cout << "Le fichier résultat s'appelle transcription.txt" << std::endl;
    }
    else if (flag and ending (title, ".txt", len, 4)){
        std::ifstream f (title);
        f.seekg (0, f.end);
        int fileLen = f.tellg ();
        f.seekg (0, f.beg);
        char* content = new char [fileLen];
        f.read (content, fileLen);
        toMorse (content);
        std::cout << "Le fichier résultat s'appelle transcription.wav" << std::endl;
    }
    else{
        toMorse (title);
        std::cout << "Le fichier résultat s'appelle transcription.wav" << std::endl;
    }
}