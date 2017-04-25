#ifndef DECK
#define DECK

#include <vector>
#include <iostream>
#include "CardStacks.hpp"

typedef struct {
    int type_stack;
    int id_stack;
} stack_id_t;


class Deck {

public: // TODO after debugging make private
    std::vector<CardStacks::WorkingPack *> workingPacks;
    std::vector<CardStacks::TargetPack *> targetPacks;
    CardStacks::RemainingPack *remaining_pack;



public:
    Deck();
    ~Deck();

    void save(std::string output_file);
    void load(std::string input_file);

    /**
     * This function creates a deck of cards, shuffle cards 'shuffles' times and
     * put cards into stacks on deck.
     * @param shuffles
     */
    void prepareDeck(unsigned char shuffles);

    /**
     * Move n card from stack src to stack dst, if it is possible.
     * Throw exception on error.
     * @param src
     * @param dst
     * @param num_of_cards
     */
    void move_from_to(stack_id_t src, stack_id_t dst, unsigned num_of_cards);

    /**
     * Make card visible on working pack with id 'id_stack'.
     * Counting from 0.
     * Check if card is already visible.
     * @param id_work_pack
     */
    void turn_card(int id_work_pack);

    /**
     * same as turn_card, but with out check.
     * @param id_work_pack
     */
    void force_turn_card(int id_work_pack);

    /**
     * If remaining pack is o the end, you can turn pack tiwh this function and go to
     * begining of pack.
     */
    void roll_rem_pack();

    /**
     * Get remaining pack back to end.
     */
    void roll_back_rem_pack();

    /**
     * Show next card in remaining pack.
     */
    void get_next_remmaining_card();

    /**
     * Show previous card in remaining pack.
     */
    void get_previous_remaining_card();
};


#endif //DEcK