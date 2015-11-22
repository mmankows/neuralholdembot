#include <vector>
#include "HoldemGame.h"

using namespace std;
HoldemGame::HoldemGame() {
    this->hand_strength = 0;
    this->position      = 0;
    this->pot           = 0;
    this->round_pot     = 0; 
    this->stack         = 0;
    this->round         = PREFLOP;
    this->rounds[round] = 1;
    this->rounds[1] = rounds[2] = rounds[3] = 0;

}

int HoldemGame::next_round() {
    this->rounds[this->round] = 0;
    this->rounds[++this->round] = 1;
    return this->round;
}

//get current game state as input fann data to test on neural network
vector<float> HoldemGame::as_state() {
    vector<float> vec;
    vec.push_back( this->hand_strength );
    vec.push_back( this->position );
    vec.push_back( this->pot );
    vec.push_back( this->round_pot );
    vec.push_back( this->stack );
    for(int i=0; i<4; i++) {
        vec.push_back( this->rounds[i] );
    }
    return vec;
}
