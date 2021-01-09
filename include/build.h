#ifndef BUILT
#define BUILT

#include <iostream>
#include <fstream>

#include "write.h"
#include "read.h"
#include "translation.h"

void toMorse (const char*);

void fromMorse (const char*);

bool ending (const char*, const char*, const int, const int);

void recognise (const char*);

#endif