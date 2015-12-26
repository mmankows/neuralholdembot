#ifndef HOLDEM_DECISION_H
    #define HOLDEM_DECISION_H
    
    #include <boost/lexical_cast.hpp>
    #include <string>
    #include "fann.h"
    #include "Constants.h"
    #include "Utils.h"

    
using boost::lexical_cast;
class Decision {
public:
    int max_amount; 
    int min_amount;

    int amount;
    int type;

    Decision() {}
    Decision(int type, int min_amount, int max_amount);
    Decision(std::string raw_decision);

    // get decision string for given amount
    std::string get();
};

#endif

