
#include "Deck.hpp"
#include "Command.hpp"

Command::Command(Deck *deck) {
    this->deck = deck;
}

void Command::make_command(cmd_t) {

}
