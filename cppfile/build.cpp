#include "../include/build.h"

void toMorse (const char* text){
    std::map <char, int> dict = buildMap ();
    std::ofstream ofile ("transcription.wav", std::ios::binary);
    Write w (ofile);
    for (int j = 0; text [j]; j++){
        if (dict.find (letterCast (text [j])) != dict.end ()){
            w.addLetter (dict[letterCast (text [j])]);
        }
        else{
            // Si le caractère n'est pas dans le dictionnaire, on l'ignore
        }
    }
    // appel implicite du destructeur de Write qui complète le header et ferme le fichier
}

void fromMorse (const char* title){
    std::ifstream ifile (title, std::ios::binary);
    Read r (ifile); // fichier audio à lire
    std::vector <double> sequence = r.fill ();
    double unit = max (sequence)/3; // longueur d'un point
    // dans la suite, ce qui nous intéresse sera alors uniquement le vecteur sequence (on peut supprimer r)
    // dans sequence, le son est aux indices pairs et les silences aux indices impairs
    const char* graphe = buildTree (); // représente un arbre
    int cur = 0;
    std::ofstream f ("transcription.txt"); // fichier qui va contenir la transcription
    // Traitement de sequence
    const int L = sequence.size (); 
    for (int k = 0; k < L; k += 2){
        if (sequence [k] > 1.5*unit and 2*cur < 62){
            cur = 2*cur + 2; // on se déplace vers le fils droit
        }
        else if (sequence [k] > unit*0.5 and 2*cur < 63){
            cur = 2*cur + 1; // on se déplace vers le fils gauche
        }
        if (k + 2 >= L and cur){
            f << graphe [cur];
        }
        else if (sequence [k + 1] > 1.5*unit){
            f << graphe [cur];
            cur = 0;
        }
    }
    f.close ();
}

bool ending (const char* title, const char* ext, const int ltitle, const int lext){
    // les deux derniers arguments sont des tailles de chaînes de caractères (sans compter le caractère final)
    if (ltitle < lext){ return false; }
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