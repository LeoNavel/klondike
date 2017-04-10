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
        void push(card::Card card);

        void pop();

        card::Card top();

        card::Card topAndPop();

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
        void push_invisible(card::Card card);

        void pop();
        void popInvisivle();

        card::Card topVisivle();
        card::Card topInvisivle();

        void turn_invisible();
    };


    class RemainingPack: public GenericCardStack {
    private:
        int current_card;

    public:
        RemainingPack();
        void popCurrent();

        // v klude metody premenuj ja som to len tak z hlavy strelil :D
        bool isSetCurrent(); // na zistenie ci je aspon jedna karta uz pretocena
        card::Card currentCard(); // na zistenie aka karta je current
        void nextCard(); // na zobrazenie dalsej karty (treba riesit aj to ked uz budu vsetky pretocene)
        bool allCardVisible(); // na zistenie ci sa uz vsetky karty pretocili
        // to ze namiesto visiBle pises obcas visiVle je schvalne? :D

    };


    class CardDeck : public CardStacks::GenericCardStack {
    public:
        CardDeck();

        void shuffleCards();
    };

}
#endif //KLONDIKE_CARDSTACKS_HPP
