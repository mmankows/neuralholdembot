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
void HoldemBot::train(std::vector<GameState> game_states) {
    for( std::vector<GameState>::iterator it=game_states.begin(); it!=game_states.end(); it++ ) {

    }
}

fann_type* HoldemBot::query(std::vector<float> inputs) {
    fann_type* fann_inputs;
    fann_type* fann_outputs;
    fann_inputs = new fann_type[inputs.size()];
    

    fann_outputs = fann_run(this->net, fann_inputs);
    std::cout<<"outputs:"
    <<fann_outputs[0]<<" "
    <<fann_outputs[1]<<" "
    <<fann_outputs[2]<<" "
    <<fann_outputs[3]<<"\n"
    ;
    delete [] fann_inputs;
    return fann_outputs;
}

Decision HoldemBot::decide( GameState& state ) {
    return random_decision(state);
    //TODO or decision from neural network
}
    
Decision HoldemBot::random_decision( GameState& state ) {
    std::vector<Decision> possible = state.possible_decisions();
   
    Decision decision = possible[ rand() % possible.size() ];
    decision.amount = (rand() % decision.max_amount) - decision.min_amount;
    return decision;
}


