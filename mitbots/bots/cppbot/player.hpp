#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Player {
 public:
  Player();
  void run(tcp::iostream &stream);
};

#endif  // __PLAYER_HPP__
