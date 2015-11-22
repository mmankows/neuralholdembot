#include <iostream>
#include "player.hpp"

Player::Player() {
}

/**
 * Simple example pokerbot, written in C++.
 *
 * This is an example of a bare bones pokerbot. It only sets up the socket
 * necessary to connect with the engine (using a Boost iostream for
 * convenience) and then always returns the same action.  It is meant as an
 * example of how a pokerbot should communicate with the engine.
 */
void Player::run(tcp::iostream &stream) {
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
