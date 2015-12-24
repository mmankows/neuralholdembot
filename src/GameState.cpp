#include "GameState.h"
#include "Utils.h"
#include <boost/lexical_cast.hpp>


#define TOKEN_DELIM ' '

#define NEWGAME_LENGTH 6
#define NEWGAME_BB_POS -3
#define NEWGAME_STACK_POS -4
#define NEWGAME_OP_POS 2



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
    int ntokens = tokens.size();
    
}

// whenever action from bot is needed
bool GameState::parse_getaction( std::string line ) {
    std::vector<std::string> tokens = split(line, TOKEN_DELIM);
    int ntokens = tokens.size();

    
    Decision d;
    d.type = FOLD;
    _possible_decisions.push_back(d);
}
    


