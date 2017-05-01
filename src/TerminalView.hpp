#ifndef TERMINAL_VIEW_H
#define TERMINAL_VIEW_H

#include "View.hpp"
#include "TerminalCanvas.hpp"

class TerminalView  : public GenericView {
private:
    TerminalCanvas canvas;

public:
    TerminalView(){canvas  = TerminalCanvas();}

    void refresh();
    int run();

    virtual void update(int id, card::Card * topTargetCard);
    virtual void update(int id, CardStacks::GenericCardStack workingPack);
    virtual void update(CardStacks::RemainingPack *remainigPack);
    virtual void highlightNextCardCommand();
    virtual void highlightRemainingToWorking(unsigned int id);
    virtual void highlightRemainingToTarget(unsigned int id);
};

#endif //TERMINAL_VIEW_H