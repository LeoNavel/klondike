/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         CARD Definition
 *
 ***************************************/
#include <algorithm>
#include "Card.hpp"


namespace Card {

        color get_card_color(card_t card) {
            if (card.card_sign == HEART || card.card_sign == DIAMONDS) {
                return RED;
            } else {
                return BLACK;
            }
        }
/*

*/
}
