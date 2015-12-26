#include <iostream>
#include <cstdlib>
#include "HoldemBot.h"

// start empty
HoldemBot::HoldemBot() {
    this->net = fann_create_standard(
                    LAYERS_COUNT,
				    INPUT_FEATURES_COUNT, 
                    NEURONS_HIDDEN_COUNT, 
                    OUTPUT_FEATURES_COUNT);
	
    fann_set_activation_function_hidden(net, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(net, FANN_SIGMOID_SYMMETRIC);
    fann_set_training_algorithm(net, FANN_TRAIN_INCREMENTAL);
	fann_set_learning_momentum(net, 0.6f);
    set_rand_factor(20);
}

HoldemBot& HoldemBot::operator=(const HoldemBot& other) {
    this->net= fann_copy(other.net);
    return *this;
}

HoldemBot::HoldemBot(const HoldemBot& other) {
    this->net= fann_copy(other.net);
}

// loads exisitng network
void HoldemBot::load( std::string network_file_path ) {
    this->net = fann_create_from_file( network_file_path.c_str() );
}

// saves network
void HoldemBot::save(std::string saved_network_path) {
	fann_save(this->net, saved_network_path.c_str() );
}

HoldemBot::~HoldemBot() {
	fann_destroy(this->net);
}

//train on input data
void HoldemBot::train(int prize, std::vector<GameState> game_states) {
    //train only if we made proper decisions
    //training intesiveness scaled to prize size
    if( prize>0 ) { 
        int max_training_cycles = prize/game_states[0].big_blind();
        for(int training_cycle=0; training_cycle<max_training_cycles; training_cycle++)
            for( std::vector<GameState>::iterator it=game_states.begin(); it!=game_states.end(); it++ ) {
                fann_type* in  = (*it).input_as_fann_data();
                fann_type* out = (*it).output_as_fann_data();

                fann_train(this->net, in, out);
            
                delete [] in;
                delete [] out;
            }
    }
}

Decision HoldemBot::decide( GameState& state ) {

    ann_decision(state);
    if( (1 + rand() % 100) <= this->rand_factor() ) 
        return random_decision(state);
    else 
        return ann_decision(state);
}
    
Decision HoldemBot::random_decision( GameState& state ) {
    std::vector<Decision> possible = state.possible_decisions();
   
    Decision decision = possible[ rand() % possible.size() ];
    decision.amount = (rand() % decision.max_amount) - decision.min_amount;

    state.set_decision_made( decision );
    return decision;
}


//FIXME
//probably leaks here!!
Decision HoldemBot::ann_decision( GameState& state ) {
    fann_type* input   = state.input_as_fann_data();
    fann_type* output = new fann_type[OUTPUT_FEATURES_COUNT]();


    std::cout<<"<><><><>ANN INPUT<><><><><>\n";
    for(int i=0; i<INPUT_FEATURES_COUNT; i++) 
        std::cout<<"F"<<i<<"="<<input[i]<<"||";
    std::cout<<"\n";

    output = fann_run(this->net, input);
    std::cout<<"<><><><>ANN DECISIONS<><><><><>\n";
    for(int i=0; i<OUTPUT_FEATURES_COUNT; i++) 
        std::cout<<"F"<<i<<"="<<output[i]<<"||";

    std::cout<<"\n";

    //delete [] input;
    //delete [] output;
}
/*                
for(int i=0; i<INPUT_FEATURES_COUNT; i++) 
std::cout<<"F"<<i<<"="<<in[i]<<"||";

std::cout<<"\n";
for(int i=0; i<OUTPUT_FEATURES_COUNT; i++) 
std::cout<<"F"<<i<<"="<<out[i]<<"||";
std::cout<<"\n";

*/
