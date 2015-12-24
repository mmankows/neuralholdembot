#include <string>
#include <iostream>
#include <exception>
#include "Game.h"

Game::Game(HoldemBot &mybot, std::string host, int port) {
    this->mybot = mybot;
    this->host  = host;
    this->port  = port;
}

// Connect to the engine.
void Game::start() {
    tcp::iostream stream;
    char port_buf[5];
    sprintf(port_buf, "%d", this->port);
    std::cout << "Connecting to " << this->host << ":" << this->port << "\n";
    stream.connect(this->host, port_buf);
    if (!stream) {
        std::cout << "Could not connect to " << this->host << ":" << this->port << "\n";
        return;
    }
    // Run game
    play(stream);
}

//loop actually playing with platform bot
void Game::play(tcp::iostream &stream) {

    GameState state;
    std::string line;
    while (std::getline(stream, line)) {
        // For now, just print out whatever date is read in.
        std::cout << line << "\n";

        // known tokens
        std::string new_game("NEWGAME");
        std::string new_hand("NEWHAND");
        std::string get_action("GETACTION");
        std::string request_keyvalue_action("REQUESTKEYVALUES");
        std::string hand_over("HANDOVER");
        std::string directive = line.substr(0, line.find_first_of(' '));

        //init new state for new hand
        if( new_game == directive ) {
            state = GameState();
            state.parse_newgame(line);
        } else if( new_hand == directive ) {
            state.parse_newhand(line);
        } else if( get_action == directive ) {
            state.parse_getaction(line);

            Decision decision = mybot.decide(state);
             
            // Respond with CHECK when playing, you'll want to change this.
            std::cout<<"MY DECISION="<<decision.get()<<std::endl;
            stream << "CHECK\n";
            game_states.push_back( state );
        } else if ( hand_over == directive ) {
            state.parse_handover(line);

            mybot.train( game_states );
            game_states.clear();
        } else if (request_keyvalue_action == directive ) {
            stream << "FINISH\n";
        }
    }

    std::cout << "Gameover, engine disconnected.\n";
}
