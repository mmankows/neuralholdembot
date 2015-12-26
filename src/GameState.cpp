#include "GameState.h"
#include "Utils.h"
#include <boost/lexical_cast.hpp>


#define TOKEN_DELIM ' '

#define NEWGAME_LENGTH 6
#define NEWGAME_BB_POS -3
#define NEWGAME_STACK_POS -4
#define NEWGAME_OP_POS 2

#define NEWHAND_POS_POS 2
#define NEWHAND_C1_POS 3
#define NEWHAND_C2_POS 4

#define GETACTION_POT_POS    1
#define GETACTION_NCARDS_POS 2
#define GETACTION_CARDS_POS 3



//init statics
int GameState::BB = 0;
int GameState::MAX_STACK = 0;
std::map<std::string,bool> GameState::OPPONENTS;
//



std::vector<Decision> GameState::possible_decisions() {
    return this->_possible_decisions;
}

void GameState::add_opponent(std::string opp_name) {
    GameState::OPPONENTS.insert( std::pair<std::string,bool>(opp_name, true));
}


// at the beggining of each match
bool GameState::parse_newgame( std::string line ) {
    std::vector<std::string> tokens = split(line, TOKEN_DELIM);
    int ntokens = tokens.size();
    int nopponents = ntokens - NEWGAME_LENGTH;

    // parse big blind 
    GameState::BB = boost::lexical_cast<int>(tokens[ntokens+NEWGAME_BB_POS]);

    // parse starting stack
    GameState::MAX_STACK = boost::lexical_cast<int>(tokens[ntokens+NEWGAME_STACK_POS]);

    // parse opponents
    for(int i=0; i<nopponents; i++) {
        add_opponent(tokens[NEWGAME_OP_POS+i]);
    }
}

// at the beggining of each hand
bool GameState::parse_newhand( std::string line ) {
    std::vector<std::string> tokens = split(line, TOKEN_DELIM);

    // parse initial position
    this->_position = boost::lexical_cast<int>(tokens[NEWHAND_POS_POS]);

    // parse my private cards
    this->_my_cards.push_back(tokens[NEWHAND_C1_POS]);
    this->_my_cards.push_back(tokens[NEWHAND_C2_POS]);
}

// whenever action from bot is needed
bool GameState::parse_getaction( std::string line ) {
    std::vector<std::string> tokens = split(line, TOKEN_DELIM);
    int ntokens = tokens.size();
    int ptr = GETACTION_POT_POS;
    
    //parse pot size
    this->_pot = boost::lexical_cast<int>(tokens[ptr]);
    
    //parse cards and calculate strength
    std::vector<std::string> all_cards = this->_my_cards; //copy my two cards
    ptr = GETACTION_NCARDS_POS;
    int ncards = boost::lexical_cast<int>(tokens[ptr++]);
    if( ncards > 0 ) {
        this->_round = ncards - 2; //3=flop,4=turn,5=river
        //int cards_begin = GETACTION_CARDS_POS
        
        for(int i=0; i<ncards; i++) {
            all_cards.push_back(tokens[ptr++]);
        }
    }
    this->_card_rank = score_cards(all_cards); 

    //player stacks, get my
    for(int i=0; i<GameState::opp_number()+1; i++) {
        if( i+1==this->position() ) { 
            this->_stack = boost::lexical_cast<int>(tokens[ptr]);
        }
        ptr++;
    }

    //active players, update position
    int nactive_players = boost::lexical_cast<int>(tokens[ptr++]);
    if( nactive_players > 0 ) {
        for(int i=0; i<GameState::opp_number()+1; i++) {
            //TODO update position
            bool is_active = (bool) tokens[ptr++].compare("false");
            std::cout<<"["<<i<<"] "<<tokens[ptr-1]<<"IS ACTIVE? "<<is_active<<"\n";
            if( i+1<this->position() && !is_active ) {
                std::cout<<"MY POS -- \n";
                --this->_position;
            }
        }
    }

    //last actions 
    int nlast_actions = boost::lexical_cast<int>(tokens[ptr++]);
    if( nlast_actions > 0 ) {
        for(int i=0; i<nlast_actions; i++) {
            //TODO do nothing??
            ptr++;
        }
    }

    //get legal actions to do
    int nlegal_actions = boost::lexical_cast<int>(tokens[ptr++]);
    this->_possible_decisions.clear();
    if( nlast_actions > 0 ) {
        for(int i=0; i<nlegal_actions; i++) {
            this->_possible_decisions.push_back( Decision(tokens[ptr++]) );
        }
    }
}
    


