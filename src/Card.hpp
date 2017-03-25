/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb??,xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         CARD Definition
 *
 ***************************************/
#ifndef CARD
#define CARD

namespace Card {


    const int KING  = 13;
    const int QUEEN = 12;
    const int JACK  = 11;

    enum sign {SPADES, HEART, CLUBS, DIAMONDS};
    enum color {BLACK, RED};
    typedef struct {
        sign   card_sign;
        int     number;
    } card_t;

    color get_card_color(card_t card);

};


#endif //CARD