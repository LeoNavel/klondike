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

    /**
     * update top card in target deck
     *
     * @param id id of target deck
     * @param topTargetCard top card
     */
    virtual void update(int id, card::Card * topTargetCard);

    /**
     * update woking deck
     *
     * @param id working deck id
     * @param workingPack working deck data
     */
    virtual void update(int id, CardStacks::GenericCardStack workingPack);

    /**
     * update remaining deck
     *
     * @param remainigPack remaining deck data
     */
    virtual void update(CardStacks::RemainingPack *remainigPack);

    /**
     * highlight next card move
     */
    virtual void highlightNextCardCommand();

    /**
     * highlight move card from remaining to working deck
     *
     * @param id working deck id
     */
    virtual void highlightRemainingToWorking(unsigned int id);

    /**
     * highlight move card from remaining to target deck
     *
     * @param id target deck id
     */
    virtual void highlightRemainingToTarget(unsigned int id);

    /**
     * highlight move card from working to target deck
     *
     * @param workingDeckID working deck id
     * @param targetDeckID target deck id
     */
    virtual void highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID);

    /**
     * highlight move cards from working deck to another working deck
     *
     * @param sourceID source working deck id
     * @param count count of cards
     * @param destinationID destination working deck id
     */
    virtual void highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID);


    /**
     * run finish game animations
     */
    virtual void finishGame();
};

#endif //TERMINAL_VIEW_H
