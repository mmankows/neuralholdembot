#include "Decision.h"    


Decision::Decision(int type, int min_amount, int max_amount) {
    this->min_amount = min_amount;
    this->max_amount = max_amount;
    this->type = type;
}

Decision::Decision(std::string raw_decision) {
    std::vector<std::string> tokens = split(raw_decision,':');
    int ntokens = tokens.size();
    std::string action = tokens[0];


    if ( ntokens == 1 ) {
        if( action == std::string("FOLD") ) {
            this->type = FOLD;
        } else {
            this->type = CHECK;
        }
    } else if ( ntokens == 2 ) {
        this->type = CALL;
        this->min_amount = this->max_amount = this->amount = boost::lexical_cast<int>(tokens[1]);
    } else if ( ntokens == 3 ) {
        if( action == std::string("BET") ) {
            this->type = BET;
        } else {
            this->type = RAISE;
        }
        this->min_amount = boost::lexical_cast<int>(tokens[1]);
        this->max_amount = boost::lexical_cast<int>(tokens[2]);
    }
}

// get decision string for given amount
std::string Decision::get() {
    
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

