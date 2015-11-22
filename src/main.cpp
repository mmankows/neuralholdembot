#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <exception>
#include "fann.h"
#include "HoldemBot.h"
#include "HoldemGame.h"

namespace opt = boost::program_options;
int main(int argc, char *argv[])
{
  // Parse out command line options.
  // Usage: pokerbot [-h HOST] PORT
  std::string host               = "localhost";
  std::string training_file_path = "";
  std::string network_file_path  = "";
  int port;
  opt::options_description desc("Allowed options");
  desc.add_options()
    ("host,h",  opt::value<std::string>(&host), "HOST")
    ("train,t", opt::value<std::string>(&training_file_path), "TRAINING")
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
    std::cout << "Usage: pokerbot [-h HOST -p PORT -n NETWORK -t TRAINING]\n";
    std::cerr << e.what() << std::endl;
    return 1;
  }

  // Initialization of bot
  HoldemBot mybot;
  if ( vm.count("net") ) {
        mybot = HoldemBot(network_file_path);
  }

  if( vm.count("train") ) {
        mybot.train(training_file_path,300,10);
        mybot.save();
  }
  
  // Connect to the engine.
  tcp::iostream stream;
  if ( vm.count("port") ) { 
      char port_buf[5];
      sprintf(port_buf, "%d", port);
      std::cout << "Connecting to " << host << ":" << port << "\n";
      stream.connect(host, port_buf);
      if (!stream) {
        std::cout << "Could not connect to " << host << ":" << port << "\n";
        return 1;
      }
      // Run game
      mybot.run(stream);
  }
    
  return 0;

}
