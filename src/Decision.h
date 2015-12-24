#ifndef HOLDEM_DECISION_H
    #define HOLDEM_DECISION_H
    
    #include <boost/lexical_cast.hpp>
    #include <string>
    #include "fann.h"
    #include "Constants.h"

    
using boost::lexical_cast;
class Decision {
public:
    int max_amount; 
    int min_amount;

    int amount;
    int type;

    Decision() {}
    Decision(int type, int min_amount, int max_amount) {
        this->min_amount = min_amount;
        this->max_amount = max_amount;
        this->type = type;
    }

    // get decision string for given amount
    std::string get() {
        
        amount = amount<max_amount?amount:max_amount;
        amount = amount>min_amount?amount:min_amount;
        std::string amount_str = boost::lexical_cast<std::string>(amount);

        switch( type ) {
            case FOLD:
                return std::string("FOLD");
            case CHECK:
                return std::string("CHECK");
            case CALL:
                amount_str = boost::lexical_cast<std::string>(max_amount);
                return std::string("CALL:") + amount_str;
            case BET:
                return std::string("BET:") + amount_str;
            case RAISE:
                return std::string("RAISE:") + amount_str;
            default: //checking is always valid
                return std::string("CHECK");
        }
    }

};

#endif

