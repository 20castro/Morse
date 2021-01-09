#include "wave.h"

void Wavfile::addBytes (int value, int size){ // en little-endian
    for (; size; size--, value >>= 8){
        file.put (static_cast <char> (value & 255));
    }
}

int Wavfile::pickBytes (int size){ // en little-endian
    int res = 0;
    int pow = 1;
    for (; size; size--, pow *= 256){
        res += pow*file.get ();
    }
    return res;
}

void Wavfile::closeFile (){
    file.close ();
}