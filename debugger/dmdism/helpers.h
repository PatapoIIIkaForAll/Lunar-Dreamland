#pragma once

#include <string>
#include <sstream>
#include "byond_structures.h"

std::string byond_tostring(int idx);
int intern_string(std::string str);
std::string tohex(int numero);
std::string todec(int numero);