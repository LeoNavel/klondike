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

private:
    /**
     * Initialize inner vectors of objects.
     */
    void init();


public:
    /**
     * Initialize stacks for deck.
     * Call init();
     */
    Deck();

    /**
     * Call init().
     * Call load(input_file);
     * @param input_file Configuration file with saved game.
     */
    Deck(std::string input_file);

    /**
     * Dele all dynamically allocated stacks.
     */
    ~Deck();

    /**
     * Save game into configuration file.
     * @param output_file Name of file.
     */
    void save(std::string output_file);

    /**
     * Load game from configuration file.
     * @param input_file Name of file.
     */
    void load(std::string input_file){}

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

    /**
     * Get copy of specified stack.
     * @param stack ID of stack, see stack_id_t
     * @return GenericCardStack object with cards copied from specified stack.
     */
    CardStacks::GenericCardStack get_pack(stack_id_t stack); // TODO

    /**
     * Get top card from specified target pack.
     * @param id_pack ID of remaining pack.
     * @return Card
     */
    card::Card get_top_card_from_target_pack(int id_pack);

    /**
     * Get ptr to remaining pack. It does't need to be specified, because this stack is only one.
     * @return pointer to Remaining pack.
     */
    CardStacks::RemainingPack *get_ptr_2_rem_pack();
};


#endif //DECK