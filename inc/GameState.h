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
    static std::string BOT_NAME; //own bot name
    int _round,_position,_stack,_pot,_card_rank;
    
    //what are legal decision in a given state
    std::vector<Decision> _possible_decisions;
    //which decision was made in this state
    Decision _decision_made;
    //my hand cards
    std::vector<std::string> _my_cards;
    
public:
    GameState() {
        _round=PREFLOP;
        _position=BUTTON;
    }

    std::vector<Decision> possible_decisions();
    
    // shared hand data
    static void add_opponent(std::string);
    static int max_stack()  { return GameState::MAX_STACK; }
    static int big_blind()  { return GameState::BB; }
    static int opp_number() { return GameState::OPPONENTS.size(); }

    // different at each decision
    int round()    { return _round;}
    int position() { return _position;}
    int stack()    { return _stack;};
    int pot()      { return _pot;}
    int card_rank(){ return _card_rank;} 
    
    // save what was decided
    void set_decision_made(Decision d) { _decision_made = d; }
    Decision decision_made() { return _decision_made; }

    // parsing engine messages
    static void parse_newgame( std::string line );
    void parse_newhand( std::string line );
    void parse_getaction( std::string line );
    int parse_handover( std::string line ); //return won prize
};
#endif
