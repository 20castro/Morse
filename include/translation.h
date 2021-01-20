#ifndef DEF_TRAD
#define DEF_TRAD

#include <map>
#include <string>

#include "tree.h"

const char letterCast (const char&); // traduit les majuscules en minuscules si nécessaire

std::map <char, int> buildMap ();
Tree buildTree ();

#endif