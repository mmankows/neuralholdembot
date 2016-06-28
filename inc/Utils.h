#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include "SevenEval.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
float score_cards(std::vector<std::string> cards_str);
float scale(int val, int min, int max);

// private 
void init_scores(void);
float score_2_cards(std::string c1, std::string c2);
int suit2int(std::string card);
int face2int(std::string card);
int card2int(std::string card);
