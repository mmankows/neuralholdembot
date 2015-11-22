#ifndef HOLDEMBOT_H
#define HOLDEMBOT_H
 
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include "fann.h"

using boost::asio::ip::tcp;
class HoldemBot {

private:
    std::string network_file_path; 
    // neural network parameters
	static const unsigned int NUM_LAYERS         = 3;
	static const unsigned int NUM_NEURONS_HIDDEN = 90;
    static const int          NUM_INPUT          = 9;
    static const int          NUM_OUTPUT         = 4;
	static const float        DESIRED_ERROR      = 0.001;
     //network itself
    struct fann *net;                  	

public:
    HoldemBot();                    //start with empty net
    HoldemBot(std::string network_file_path); //init from file
    ~HoldemBot();
    HoldemBot(const HoldemBot& other);
    HoldemBot& operator=(const HoldemBot&);
    
    void run(tcp::iostream& stream); 
    fann_type* query(std::vector<float> inputs);
    void train(std::string train_file_name, int epochs, int debug_interval=0);
    void test(std::string  test_file_name);
    void save();
    

};

#endif
