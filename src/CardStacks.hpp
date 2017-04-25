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

/**
 * This is sepaate namespace for stacks
 */
namespace CardStacks{

    /**
     * @brief Abstraction of card stack. From this stack inherite every other stack.
     */
    class GenericCardStack {
    protected:
        std::vector<card::Card> card_stack; /**< Vector of cards. Here are cards stored */

    public:
        // add card to top of stack
        void push(card::Card card);

        // remove card from top fo stack
        void pop();

        // copy card object from top of stack
        card::Card top();

        // calling top and pop
        card::Card topAndPop();

        // check if there is any card in stack
        bool isEmpty();

        // get number of cards
        unsigned long size();

        //print every card in stack
        // debug function
        void printContent();

    };


    class TargetPack : public GenericCardStack {
    public:
        // overriding push, you can push only with preconditions
        void push(card::Card card);
    };


    class WorkingPack : public GenericCardStack{
    public:
        void push(card::Card card);
        void push_invisible(card::Card card);

        bool anyVisible();

        void pop();
        void popInvisible();

        card::Card topVisible();
        card::Card topInvisible();

        void turn_invisible();

        void print();
    };


    class RemainingPack: public GenericCardStack {
    private:
        int current_card;

    public:
        RemainingPack();
        void popCurrent();
        card::Card topAndPopCurrent();

        // v klude metody premenuj ja som to len tak z hlavy strelil :D
        bool isSetCurrent(); // na zistenie ci je aspon jedna karta uz pretocena
        card::Card currentCard(); // na zistenie aka karta je current
        void insertCurrent(card::Card);
        void nextCard(); // na zobrazenie dalsej karty (treba riesit aj to ked uz budu vsetky pretocene)
        bool allCardVisible(); // na zistenie ci sa uz vsetky karty pretocili

        void turnPack();

    };


    class CardDeck : public CardStacks::GenericCardStack {
    public:
        CardDeck();

        void shuffleCards();
    };

}
#endif //KLONDIKE_CARDSTACKS_HPP
