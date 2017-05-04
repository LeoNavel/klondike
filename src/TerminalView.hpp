/*! 
 *  \file       TerminalView.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef TERMINAL_VIEW_H
#define TERMINAL_VIEW_H

#include "View.hpp"
#include "TerminalCanvas.hpp"

class TerminalView  : public GenericView {
private:
    TerminalCanvas canvas;

public:
    TerminalView();

    void refresh();
    int run();
    void help();

    virtual void update(int id, card::Card * topTargetCard);
    virtual void update(int id, CardStacks::GenericCardStack workingPack);
    virtual void update(CardStacks::RemainingPack *remainigPack);
    virtual void highlightNextCardCommand();
    virtual void highlightRemainingToWorking(unsigned int id);
    virtual void highlightRemainingToTarget(unsigned int id);
    virtual void highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID);
    virtual void highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID);
};

#endif //TERMINAL_VIEW_H
