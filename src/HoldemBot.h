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
    int _rand_factor;
    struct fann *net;                  	

protected:
    Decision random_decision( GameState& state );
    Decision ann_decision( GameState& state );

public:
    HoldemBot();                    //start with empty net
    ~HoldemBot();
    HoldemBot(const HoldemBot& other);
    HoldemBot& operator=(const HoldemBot&);

    int rand_factor() { return _rand_factor; }
    int set_rand_factor(int rand_factor) { this->_rand_factor=rand_factor; }

    Decision decide( GameState& state ); 
    void train(int prize, std::vector<GameState> game_states);
    void load(std::string saved_net_path); //init from file
    void save(std::string saved_net_path);

};

#endif
