#include "Command.hpp"


int main(){

    Deck *deck = new Deck();
    Command *cmd = new Command(deck);

    deck->prepareDeck(6);

    for (auto &&workingPack :deck->workingPacks) {
        workingPack->print();
    }



    delete cmd;
    delete deck;
    return EXIT_SUCCESS;
}