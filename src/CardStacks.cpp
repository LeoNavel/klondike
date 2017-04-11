/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         Stack definitions
 *
 ***************************************/
#include <iostream>
#include <algorithm>
#include "CardStacks.hpp"
#include "Card.hpp"
#include "Error.hpp"

namespace CardStacks {

    /**
     * @brief Put card on top of stack.
     * @param card Play card object.
     */
    void GenericCardStack::push(card::Card card) {
        this->card_stack.push_back(card);
    }

    /**
     * @brief Remove card from top of stack.
     */
    void GenericCardStack::pop() {
        if (!this->isEmpty()) {
            this->card_stack.pop_back();
        }
    }

    /**
     * @brief Remove card from stack and return that object of card.
     * @return Card that is being removed from stack;
     */
    card::Card GenericCardStack::topAndPop() {
        card::Card poped_card = top();
        pop();
        return poped_card;
    }

    /**
     * @brief Check if stack is empty.
     * @return bool value, if stack is empty
     */
    bool GenericCardStack::isEmpty() {
        return !static_cast<bool>(this->card_stack.size());
    }

    /**
     * @brief Get number of cards in stack.
     * @return Number of cards of stack
     */
    unsigned long GenericCardStack::size() {
        return card_stack.size();
    }

    /**
     * @brief Print every card in stack.
     */
    void GenericCardStack::printContent() {
        for (auto &i:card_stack) {
            std::cout << "card-color:" << i.get_sign() << "  Number:" << i.get_number() << std::endl;
        }
    }

    /**
     * @brief Get card from top of stack.
     * @return card from top of stack
     */
    card::Card GenericCardStack::top() {
        if (!isEmpty()) {
            return this->card_stack[size() - 1];
        } else {
            throw "Stack: is empty";
        }
    }

    /**
     * @brief Add card to stack, if preconditions are OK
     * @param card Card to add
     * @pre Color of cards are same, top_card = add_card + 1
     */
    void TargetPack::push(card::Card card) {
        if (isEmpty()) {
            if(card.get_number() == card::ACE) {
                GenericCardStack::push(card);
            }
            else throw ErrorException(E_TARGET_PACK_PUSH, "On top might be ACE");
        } else {
            card::Card card_on_top = top();
            if (card_on_top.get_sign() == card.get_sign() &&
                    card_on_top.get_number() == card.get_number() - 1) {
                GenericCardStack::push(card);
            } else {
                throw ErrorException(E_TARGET_PACK_PUSH,"this is wrong push");
            }
        }
    }

    /**
     * @brief Adding new card to visible cards.
     * @param card New card
     * @pre Color_top != Color_new_card and top_card_num = new_card_num + 1
     */
    void WorkingPack::push(card::Card card) {
        if (visible_cards.isEmpty() && invisible_cards.isEmpty()) {
            if (card.get_number() == card::KING) {
                visible_cards.push(card);
            } else throw ErrorException(E_WORK_PACK_PUSH, "First card might be king");
        } else {
            int tmp;
            card::Card top_card = visible_cards.top();
            if (card::get_card_color(top_card) != card::get_card_color(card) &&
                    (tmp=(card.get_number() + 1)) == top_card.get_number())
            {
                visible_cards.push(card);
            }
            else throw ErrorException(E_WORK_PACK_PUSH, "Color match or numbers of cards are not in order");
        }
    }

    /**
     * @brief Adding new card to invisible cards.
     * @param card Card
     */
    void WorkingPack::push_invisible(card::Card card) {
        invisible_cards.push(card);
    }

    /**
     * @brief Removing card from visible cards.
     */
    void WorkingPack::pop() {
        if (!visible_cards.isEmpty()) {
            visible_cards.pop();
        }
    }

    /**
     * @brief Remove card from invisible
     * @pre There are no visible cards.
     */
    void WorkingPack::popInvisivle() {
        if (!invisible_cards.isEmpty() && visible_cards.isEmpty()) {
            invisible_cards.pop();
        }
        else throw ErrorException(E_WORK_PACK_POP, "popping invisible card over visible");
    }

    /**
     * @brief Get card from visibles.
     * @return Card
     */
    card::Card WorkingPack::topVisivle() {
        return visible_cards.top();
    }

    /**
     * @rief Get card from invisible stack
     * @return Card
     */
    card::Card WorkingPack::topInvisivle() {
        return invisible_cards.top();
    }

    /**
     * @brief Get card from invisible and put it to visible.
     * @pre Visible card stack si empty
     */
    void WorkingPack::turn_invisible() {
        visible_cards.push(invisible_cards.topAndPop());
    }

    /**
     * @brief Constructor
     */
    RemainingPack::RemainingPack() {
        current_card = -1;
    }

    /**
     * Get card where pointer current is pointing.
     * @return
     */
    card::Card RemainingPack::currentCard() {
        return card_stack[current_card];
    }

    /**
     * @brief Moving pointer to next card.
     */
    void RemainingPack::nextCard() {
        // casting because size() is unsigned type
        if (current_card < static_cast<long>(card_stack.size())) current_card++;
    }

    /**
     * @brief Set card pointer to 1 card befora start
     */
    void RemainingPack::turnPack() {
        current_card = -1;
    }

    /**
     * @brief all card are visible
     * @return bool if all card are visible
     */
    bool RemainingPack::allCardVisible() {
        return current_card == card_stack.size();
    }

    /**
     * @return bool if pinter is set
     */
    bool RemainingPack::isSetCurrent() {
        return (current_card >= 0);
    }

    /**
     * @brief Pop card where pointer is pointing.
     */
    void RemainingPack::popCurrent() {
        if (card_stack.size() < current_card and current_card != -1){
            card_stack.erase(card_stack.begin() + current_card);
        }
        else {
            throw ErrorException(E_REM_PACK_POP, "using popCurrent() with out set current pointer or out of range");
        }
    }

    /**
     * Get card current card a pop it out
     * @return poped card
     */
    card::Card RemainingPack::topAndPopCurrent() {
        card::Card poped_card = currentCard();
        popCurrent();
        return poped_card;
    }

    /**
     * @brief Crete a deck cards and fill it with cards.
     */
    CardDeck::CardDeck() {
        card::Card new_card(1, card::SPADES);

        new_card.set_sign(card::SPADES);
        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::HEART);

        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::CLUBS);

        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }

        new_card.set_sign(card::DIAMONDS);
        for (int i = 1; i <= card::MAX_CARD_IN_DECK ; i++){
            new_card.set_number(i);
            push(new_card);
        }
    }

    /**
     * @brief Randomize order fo cards.
     */
    void CardDeck::shuffleCards() {
        std::random_shuffle(card_stack.begin(), card_stack.end());
    }

}
