#include "Utils.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int card2int(std::string card) {
    char face = card.at(0);
    char suit = card.at(1);
    
    int face_int;
    int suit_int;

    // get score for face
    if( face >= '2' and face <= '9' ) {
        face_int = face-50; //shift
    } else {
        switch(face) {
            case 'T': face_int = 8; break;
            case 'J': face_int = 9; break;
            case 'Q': face_int = 10; break;
            case 'K': face_int = 11; break;
            case 'A': face_int = 12; break;
            default:  face_int = -1;
        }
    }
    face_int *=4; //0,4,8..48//

    // get score for suit
    switch(suit) {
        case 'c' : suit_int = 0; break; 
        case 's' : suit_int = 1; break;
        case 'd' : suit_int = 2; break;
        case 'h' : suit_int = 3; break;
    }

    return face_int + suit_int;
}
