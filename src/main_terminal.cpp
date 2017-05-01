#include "TerminalView.hpp"
#include "Controller.hpp"

int main(){
    Deck *deck = new Deck();
    //TerminalView *view = new TerminalView();
    //Controller *controller = new Controller(deck, view);

    TerminalCanvas canvas = TerminalCanvas();

    card::Card c1 = card::Card(1,card::SPADES);
    canvas.update(0,&c1);
    canvas.update(1,&c1);
    canvas.update(2,&c1);
    canvas.update(3,&c1);
    canvas.print();

    return 8;//view->run();
}