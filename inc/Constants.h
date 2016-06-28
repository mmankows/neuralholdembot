#ifndef HOLDEM_CONSTANTS_H
    #define HOLDEM_CONSTANTS_H

//
#define CHECK_THRESHOLD -0.50

// rounds
#define PREFLOP 0
#define FLOP    1
#define TURN    2
#define RIVER   3


// decisions
#define FOLD  0
#define CHECK 1
#define CALL  2
#define BET   3
#define RAISE 4

// other
#define BUTTON 1
    
// neural network parameters
#define INPUT_FEATURES_COUNT  13
#define OUTPUT_FEATURES_COUNT 6
#define LAYERS_COUNT          3
#define NEURONS_HIDDEN_COUNT  25



#endif
