#ifndef HOLDEM_GAME_STATE
    #define HOLDEM_GAME_STATE
    #include <string>
    #include <vector>
    #include <map>
    #include "fann.h"

    #include "Constants.h"
    #include "Decision.h"

class GameState {
private:
    static std::map<std::string,bool> OPPONENTS;
    static int BB; //big blind
    static int MAX_STACK; //starting stack size
    
    std::vector<Decision> _possible_decisions;
    
public:
    GameState() {}

    std::vector<Decision> possible_decisions();
    
    // game data
    static void add_opponent(std::string);
    static int max_stack() { return GameState::MAX_STACK; }
    static int big_blind() { return GameState::BB; }
    int round();
    int position();
    int stack();
    int round_pot();
    int total_pot();
    int card_rank(); 
    
    fann_type* as_fann_data();

    // parsing engine messages
    bool parse_newgame( std::string line );
    bool parse_newhand( std::string line );
    bool parse_getaction( std::string line );
    bool parse_handover( std::string line ) {};
};
#endif
