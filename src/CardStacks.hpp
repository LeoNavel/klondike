/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         CARD Definition
 *
 ***************************************/

#ifndef KLONDIKE_CARDSTACKS_HPP
#define KLONDIKE_CARDSTACKS_HPP

#include <vector>
#include "Card.hpp"


namespace CardStacks{

    class GenericCardStack {
    protected:
        std::vector<Card::card_t> card_stack;

    public:
        virtual void push(Card::card_t card);

        virtual void pop();

        Card::card_t top();

        bool isEmpty();

        unsigned long size();

        void printContent();

    };

    class TargetPack : public GenericCardStack {
    public:
        void push(Card::card_t card);
    };

    class WorkingPack{
    private:
        GenericCardStack invisible_cards;
        GenericCardStack visible_cards;

    public:
        void push(Card::card_t card);

        void pop();
        void popInvisivle();

        Card::card_t topVisivle();
        Card::card_t topInvisivle();
    };

    class RemainingPack: GenericCardStack {
    private:
        int current_card;

    public:
        RemainingPack();
        void popCurrent();

    };

    class CardDeck : public CardStacks::GenericCardStack {
    public:
        CardDeck();

        void shuffleCards();

        Card::card_t topAndPop();

    };

}
#endif //KLONDIKE_CARDSTACKS_HPP
