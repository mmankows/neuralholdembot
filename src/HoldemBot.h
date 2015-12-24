#ifndef HOLDEMBOT_H
#define HOLDEMBOT_H
 
#include <boost/asio.hpp>
#include <string>
#include <vector>

#include "Constants.h"
#include "fann.h"
#include "GameState.h"
#include "Decision.h"

using boost::asio::ip::tcp;
class HoldemBot {

private:
    std::string network_file_path; 
    // neural network
    struct fann *net;                  	

public:
    HoldemBot();                    //start with empty net
    ~HoldemBot();
    HoldemBot(const HoldemBot& other);
    HoldemBot& operator=(const HoldemBot&);
    
    fann_type* query(std::vector<float> inputs);

    Decision decide( GameState& state ); 
    void train(std::vector<GameState> game_states);
    void load(std::string saved_net_path); //init from file
    void save(std::string saved_net_path);
protected:
    Decision random_decision( GameState& state );

};

#endif
