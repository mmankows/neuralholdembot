#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <exception>

#include "fann.h"
#include "HoldemBot.h"
#include "Game.h"
#include "Utils.h"

namespace opt = boost::program_options;
int main(int argc, char *argv[])
{
    std::string host               = "localhost";
    std::string training_file_path = "";
    std::string network_file_path  = "";
    int port = 3000;
    opt::options_description desc("Allowed options");
    desc.add_options()
      ("host,h",  opt::value<std::string>(&host), "HOST")
      ("net,n",   opt::value<std::string>(&network_file_path), "NETWORK")
      ("port",    opt::value<int>(&port), "PORT")
    ;

    opt::positional_options_description p;
    p.add("port", 1);

    opt::variables_map vm;
    try {
        opt::store(opt::command_line_parser(argc, argv).
                 options(desc).positional(p).run(), vm);
        opt::notify(vm);
    } catch (const std::exception& e) {
        std::cout << "Usage: pokerbot [-h HOST -p PORT -n NETWORK]\n";
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Initialization of bot
    HoldemBot mybot;
    if ( vm.count("net") ) {
        mybot.load(network_file_path);
    }  

    Game game(mybot, host, port);
    game.start();
    
    if( network_file_path.empty() ) {
        network_file_path = "data/bot.net";
    }
    mybot.save(network_file_path);

    return 0;

}
