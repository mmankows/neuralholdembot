#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include "SevenEval.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
float score_cards(std::vector<std::string> cards_str);

// private 
float score_2_cards(int c1, int c2);
int card2int(std::string card);
