/*! 
 *  \file       Card.cpp
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
#include <algorithm>
#include "Card.hpp"


namespace card {

        color get_card_color(Card card) {
            if (card.get_sign() == HEART || card.get_sign() == DIAMONDS) {
                return RED;
            } else {
                return BLACK;
            }
        }

    sign Card::get_sign() const {
        return card_sign;
    }

    int Card::get_number() const {
        return number;
    }

    void Card::set_sign(sign card_sign) {
        Card::card_sign = card_sign;
    }

    void Card::set_number(int number) {
        Card::number = number;
    }

    Card::Card(int number, sign card_sign):Card(number, card_sign, false){}

    Card::Card(int number, sign card_sign, bool visible){
        this->number = number;
        this->card_sign = card_sign;
        this->visible = visible;
    }

    bool Card::operator==(Card other) {
        if (    this->get_number() == other.get_number() &&
                this->get_sign() == other.get_sign()){
            return true;
        }
        else return false;
    }

    bool Card::operator!=(Card other) {
        return !(this->operator==(other));
    }

    bool Card::isTurnedUp() {
        return this->visible;
    }

    void Card::turnUp() {
        this->visible = true;
    }

    void Card::turnDown() {
        this->visible = false;
    }

    std::string Card::print_card() {
        std::string ret_str;
        ret_str =  "card-color: " ;
        ret_str += std::to_string(get_sign());
        ret_str += "  Number: " + std::to_string(get_number());
        ret_str += " visible : " + std::to_string(isTurnedUp());
        return ret_str;
    }

    bool Card::get_visibility() {
        return visible;
    }

    color Card::get_color() {
        if (get_sign() == HEART || get_sign() == DIAMONDS) {
            return RED;
        } else {
            return BLACK;
        }
    }

}
