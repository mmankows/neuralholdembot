#include <iostream>
#include <cstdlib>
#include "HoldemBot.h"

// start empty
HoldemBot::HoldemBot() {
    this->net = fann_create_standard(
                    HoldemBot::NUM_LAYERS,
				    HoldemBot::NUM_INPUT, 
                    HoldemBot::NUM_NEURONS_HIDDEN, 
                    HoldemBot::NUM_OUTPUT);
	
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

HoldemBot::HoldemBot( std::string network_file_path ) {
    std::cout<<"KON STR";
    this->net = fann_create_from_file( network_file_path.c_str() );
    std::cout<<"KON STR KONIEC";
}

void HoldemBot::save() {
	fann_save(this->net, "data/holdembot.net" );
}

HoldemBot::~HoldemBot() {
	fann_destroy(this->net);
}

void HoldemBot::train(std::string train_file_name, int epochs, int debug_interval ) {
	struct fann_train_data* train_data = fann_read_train_from_file( train_file_name.c_str() );     
	
//    fann_set_scaling_params(
//		    this->net,
//			train_data,
//			0,	/* New input minimum */
//			1,	/* New input maximum */
//			0,	/* New output minimum */
//			1);	/* New output maximum */
//
//	fann_scale_train( this->net, train_data );

    fann_train_on_data(this->net, train_data, epochs, debug_interval, HoldemBot::DESIRED_ERROR);
	fann_destroy_train(train_data);
}

void HoldemBot::test(std::string test_file_name ) {
	struct fann_train_data* test_data = fann_read_train_from_file( test_file_name.c_str() );
	
    fann_reset_MSE(this->net);
	for(int i = 0; i < fann_length_train_data(test_data); i++)
	{
		fann_test(this->net, test_data->input[i], test_data->output[i]);
	}
	printf("MSE error on test data: %f\n", fann_get_MSE(this->net));
	fann_destroy_train(test_data);
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

void HoldemBot::run(tcp::iostream &stream) {
  std::string line;
  while (std::getline(stream, line)) {
    // For now, just print out whatever date is read in.
    std::cout << line << "\n";

    std::string getaction("GETACTION");
    std::string request_keyvalue_action("REQUESTKEYVALUES");
    std::string first_word = line.substr(0, line.find_first_of(' '));
    if (getaction.compare(first_word) == 0) {
      // Respond with CHECK when playing, you'll want to change this.
      stream << "CHECK\n";
    } else if (request_keyvalue_action.compare(first_word) == 0) {
      // FINISh indicates no more keyvalue pairs to store.
      stream << "FINISH\n";
    }
  }

  std::cout << "Gameover, engine disconnected.\n";
}
