#include "Utils.h"
#include "FiveEval.h"
#include "SevenEval.h"


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

float score_cards(std::vector<std::string> cards_str) {
    std::vector<int> cards;
    for(int i=0; i<cards_str.size(); i++) { // convert cards to integers
        cards.push_back( card2int(cards_str[i]) );
    }

    int rank = 0;
    SevenEval const eval7;
    FiveEval  const eval5;
    switch ( cards.size() ) {
        case 2: rank=score_2_cards(cards[0],cards[1]); break;
        case 5: rank=eval5.GetRank(cards[0],cards[1],cards[2],cards[3],cards[4]); break;
        case 6: 
                for(int i=0; i<6; i++) {
                    std::vector<int> cpy = cards;
                    cpy.erase(cpy.begin() + i );

                    int new_rank = eval5.GetRank(cpy[0],cpy[1],cpy[2],cpy[3],cpy[4]);
                    rank = rank < new_rank ? new_rank : rank;
                }
                break;
        case 7: rank=eval7.GetRank(cards[0],cards[1],cards[2],cards[3],cards[4],cards[5],cards[6]); break;
        default: rank=0;
    }

    return (rank/100);
}

float score_2_cards(int c1, int c2) {return 0.5;}

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

float scale(int val, int min, int max) {
    float n = 2 * (float(val-min)/float(max-min) - 0.5);
    n = n < -1 ? -1 : n;
    n = n >  1 ?  1 : n;
    return n;
}
