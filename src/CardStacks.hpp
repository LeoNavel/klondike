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
        std::vector<card::Card> card_stack;

    public:
        virtual void push(card::Card card);

        virtual void pop();

        card::Card top();

        bool isEmpty();

        unsigned long size();

        void printContent();

    };

    class TargetPack : public GenericCardStack {
    public:
        void push(card::Card card);
    };

    class WorkingPack{
    private:
        GenericCardStack invisible_cards;
        GenericCardStack visible_cards;

    public:
        void push(card::Card card);

        void pop();
        void popInvisivle();

        card::Card topVisivle();
        card::Card topInvisivle();
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

        card::Card topAndPop();

    };

}
#endif //KLONDIKE_CARDSTACKS_HPP
