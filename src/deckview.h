/*! 
 *  \file       deckview.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QFrame>
#include <QResizeEvent>
#include <vector>
#include "CardStacks.hpp"
#include "workingpackview.h"
#include "Card.hpp"
#include "cardselection.h"
#include "cardview.h"
#include "targetpackview.h"
#include "Controller.hpp"
#include "remainingpackview.h"
#include "View.hpp"

namespace Ui {
class DeckView;
}

class DeckView : public QFrame, public GenericView
{
    Q_OBJECT

public:
    explicit DeckView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    /**
     * prepare deck
     *
     * @param shuffles number of shuffles
     */
    void prepareDeck(unsigned char shuffles);
    CardSelection * cardSelection;

    /**
     * update remainig deck
     *
     * @param rp data of remaining deck
     */
    virtual void update(CardStacks::RemainingPack *rp);

    /**
     * update target deck view
     * @param id id
     * @param topTargetCard top card
     */
    virtual void update(int id, card::Card * topTargetCard);

    /**
     * update working pack view
     *
     * @param id id
     * @param workingPack data of working deck
     */
    virtual void update(int id, CardStacks::GenericCardStack workingPack);

    /**
     * get next card
     */
    void getNext();

    /**
     * rutn remaining cards
     */
    void turnRemainingCards();

    /**
     * move one card from remaining pack to target pack
     *
     * @param to target pack view
     */
    void moveCardsFromRemainingPack(TargetPackView * to);

    /**
     * move one cards from remaining pack to working pack
     *
     * @param to working pack view
     */
    void moveCardsFromRemainingPack(WorkingPackView *to);

    /**
     * move cards from working pack to target pack
     * @param from working pack
     * @param to target pack
     * @param count number of cards
     */
    void moveCardsToTargetPack(WorkingPackView* from, TargetPackView * to, unsigned int count);

    /**
     * move cards from working pack to another working pack
     *
     * @param from working pack
     * @param to working pack
     * @param count number of cards
     */
    void moveCards(WorkingPackView * from, WorkingPackView *to, unsigned int count);

    /**
     * highlight next card move
     */
    void highlightNextCardCommand();

    /**
     * highlight move card from remaining to working deck
     * @param id id of working deck
     */
    void highlightRemainingToWorking(unsigned int id);

    /**
     * highlight remaining to target
     *
     * @param id id of target deck
     */
    void highlightRemainingToTarget(unsigned int id);

    /**
     * highlight move card from target to working deck
     *
     * @param workingDeckID working deck id
     * @param targetDeckID target deck id
     */
    void highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID);

    /**
     * highlight move card from working to working deck
     *
     * @param sourceID source woking deck
     * @param count count of cards
     * @param destinationID destination working deck id
     */
    void highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID);

    /**
     * restart view
     */
    void restartView();

    /**
     * update cursor
     */
    void updateCursor();

    /**
     * request for update all
     */
    void requestUpdateAll();

    /**
     * finish game animation
     */
    void finishGame();

    void turnCard(WorkingPackView * on);
    virtual ~DeckView();

private:
    Ui::DeckView *ui;
    std::vector<WorkingPackView *> workingPacks;
    std::vector<TargetPackView *> targetPacks;
    std::vector<CardView *> finishGameCards;
    RemainingPackView * remainingPackView;
};

#endif // DECKVIEW_H
