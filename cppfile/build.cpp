#include "build.h"

void toMorse (const char* text){
    std::map <char, int> dict = buildMap ();
    Write w ("transcription.wav");
    for (int j = 0; text [j]; j++){
        if (dict.find (text [j]) != dict.end ()){
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
    std::ofstream f ("transcription.txt"); // fichier qui va contenir la transcription
    
    // corps

    r.closeFile ();
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