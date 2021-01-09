#include "read.h"

Read::Read (const char* nom) : file (nom, std::ios::binary){
    file.seekg (16);
    extra = pickBytes (4) - 16;
    file.seekg (22);
    channels = pickBytes (2);
    file.seekg (24);
    rate = pickBytes (4);
    file.seekg (34);
    sample = pickBytes (2);
    file.seekg (40 + extra);
    longueur = pickBytes (4);
}

void Read::setCur (int cur){
    file.seekg (cur);
}