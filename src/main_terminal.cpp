#include "TerminalView.hpp"
#include "Controller.hpp"

int main(){
    Deck *deck = new Deck();
    TerminalView *view = new TerminalView();
    Controller *controller = new Controller(deck, view);

    return view->run();
}