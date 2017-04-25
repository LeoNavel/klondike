#ifndef DECK
#define DECK

#include <vector>
#include <iostream>

#include "CardStacks.hpp"

class Deck {

public:
    std::vector<CardStacks::WorkingPack *> workingPacks;
    std::vector<CardStacks::TargetPack *> targetPacks;
    CardStacks::RemainingPack *remaining_pack;

public:
    Deck();
    ~Deck();

    void save(std::string output_file);
    void load(std::string input_file);


    void prepareDeck(unsigned char shuffles);



};


#endif //DEcK