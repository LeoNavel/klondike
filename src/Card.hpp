/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         CARD Definition
 *
 ***************************************/
#ifndef CARD
#define CARD

namespace Card {


    const int KING = 13;
    const int QUEEN = 12;
    const int JACK = 11;

    const int MAX_CARD_IN_DECK = 13;

    enum sign {
        SPADES, HEART, CLUBS, DIAMONDS
    };
    enum color {
        BLACK, RED
    };
    typedef struct {
        sign card_sign;
        int number;
    } card_t;

    /**
     * This function return color of sign in card.
     * @param card card which color is finded
     * @return color of sign
     */
    color get_card_color(card_t card);

}
#endif //CARD
