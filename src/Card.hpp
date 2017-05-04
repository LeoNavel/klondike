/*! 
 *  \file       Card.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
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

#include <iostream>

/**
 * @brief Card namespace
 *
 * This namespace shield definitions of class Card and constants important
 * to this object.
 */
namespace card {


    const int KING = 13; /**< Const for KING*/
    const int QUEEN = 12; /**< Const for QUEEN*/
    const int JACK = 11; /**< Const for JACK*/
    const int ACE = 1; /**< Const for ACE*/

    const int MAX_CARD_IN_DECK = 13; /**< Number of cards in card deck.*/

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

        /**
         * Check if cards are same.
         * @param other Seccond card object
         * @return
         */
        bool operator ==(Card other);

        /**
         * Implementing non equal check of cards.
         * @param other Second card object.
         * @return
         */
        bool operator !=(Card other);

        /**
         * Card constructor
         * @param number Card number
         * @param card_sign Card sign
         */
        Card(int number = 0, sign card_sign = SPADES);

        /**
         * Card constructor
         * @param number Card number
         * @param card_sign  Card sign
         * @param visible visibility
         */
        Card(int number, sign card_sign, bool visible);

        /**
         * Set card number.
         * @param number
         */
        void set_number(int number);

        /**
         * Set card sign.
         * @param card_sign
         */
        void set_sign(sign card_sign);

        /**
         * Get number of card.
         * @return
         */
        int get_number() const;

        /**
         * Return card sign.
         * @return
         */
        sign get_sign() const;

        /**
         * Return visibility attribute.
         * @return
         */
        bool get_visibility();

        /**
         * Get color of card.
         * @return
         */
        color get_color();

        /**
         * Check if card is visible and return result.
         * @return
         */
        bool isTurnedUp();

        /**
         * Making card visible.
         */
        void turnUp();

        /**
         * Making card invisible.
         */
        void turnDown();

        std::string print_card();
    };

    /**
     * This function return color of sign in card.
     * @param card card which color is finded
     * @return color of sign
     */
    color get_card_color(Card card);

}
#endif //CARD
