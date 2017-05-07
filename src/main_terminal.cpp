/*! 
 *  \file       main_terminal.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "TerminalView.hpp"
#include "Controller.hpp"

int main(){
    Deck *deck = new Deck();
    deck->prepareDeck(2);
    TerminalView *view = new TerminalView();
    Controller *controller = new Controller(deck, view);

    view->run();


    //delete deck;
    //delete view;
    delete controller;

    return EXIT_SUCCESS;
}