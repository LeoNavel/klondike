/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb??,xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         CARD Definition
 *
 ***************************************/
#include "Card.hpp"

using namespace Card;

color get_card_color(card_t card) {
    if (card.card_sign == HEART || card.card_sign == DIAMONDS){
        return RED;
    }
    else {
        return BLACK;
    }
}