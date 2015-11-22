#ifndef HOLDEM_GAME_H
    #define HOLDEM_GAME_H
    #include <vector>
    #include "fann.h"    

    #define PREFLOP 0
    #define FLOP    1
    #define TURN    2
    #define RIVER   3
   
using namespace std;
class HoldemGame {

private:
    float hand_strength;
    float position     ;
    float pot          ;
    float round_pot    ; 
    float stack        ;
    int   round        ;
    float rounds[4]    ;


public:
    HoldemGame();

    //increment round
    int next_round();
    //get current game state as input fann data to test on neural network
    vector<float> as_state();
};

#endif
