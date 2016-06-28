#ifndef HOLDEM_GAME_H
    #define HOLDEM_GAME_H
    #include <vector>
    #include <boost/asio.hpp>
    #include "GameState.h"
    #include "HoldemBot.h"
    
class Game {
private:
    HoldemBot mybot;
    std::vector<GameState> game_states;

    std::string host;
    int port;

public:
    Game(HoldemBot &mybot, std::string host, int port);    
    void start();
protected:
    void play(tcp::iostream &stream);

};

#endif
