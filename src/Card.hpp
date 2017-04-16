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

namespace card {


    const int KING = 13;
    const int QUEEN = 12;
    const int JACK = 11;
    const int ACE = 1;

    const int MAX_CARD_IN_DECK = 13;

    enum sign {
        SPADES, HEART, CLUBS, DIAMONDS
    };
    enum color {
        BLACK, RED
    };

    class Card {
    private:
        sign card_sign;
        int number;
        bool visible;
    public:
        bool operator ==(Card other);
        bool operator !=(Card other);
        Card(int number = 0, sign card_sign = SPADES);
        Card(int number, sign card_sign, bool visible);
        void set_number(int number);
        void set_sign(sign card_sign);
        int get_number() const;
        sign get_sign() const;
        bool isTurnedUp();
        void turnUp();
    };

    /**
     * This function return color of sign in card.
     * @param card card which color is finded
     * @return color of sign
     */
    color get_card_color(Card card);

}
#endif //CARD
