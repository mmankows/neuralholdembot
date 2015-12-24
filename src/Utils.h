#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include "SevenEval.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
int card2int(std::string card); 
int cards_eval(std::vector<std::string> cards);
