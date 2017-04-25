#ifndef DECK
#define DECK

#include <vector>
#include <iostream>
#include "CardStacks.hpp"

#define WORKING 0
#define REMMAINING 1
#define TARGET 2


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

    void move_from_to(stack_id_t src, stack_id_t dst, int num_of_cards);

    void turn_card(int id_work_pack);

    void get_next_remmaining_card();
};


#endif //DEcK