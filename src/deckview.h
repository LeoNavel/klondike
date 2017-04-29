#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QFrame>
#include <QResizeEvent>
#include <vector>
#include "CardStacks.hpp"
#include "workingpackview.h"
#include "Card.hpp"
#include "cardselection.h"
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
    void prepareDeck(unsigned char shuffles);
    CardSelection * cardSelection;
    virtual void update(CardStacks::RemainingPack *rp);
    virtual void update(int id, card::Card * topTargetCard);
    virtual void update(int id, CardStacks::GenericCardStack workingPack);
    void getNext();
    void turnRemainingCards();
    void moveCardsFromRemainingPack(TargetPackView * to);
    void moveCardsFromRemainingPack(WorkingPackView *to);
    void moveCardsToTargetPack(WorkingPackView* from, TargetPackView * to, unsigned int count);
    void moveCards(WorkingPackView * from, WorkingPackView *to, unsigned int count);
    void updateCursor();
    void requestUpdateAll();

    void turnCard(WorkingPackView * on);
    ~DeckView();

private:
    Ui::DeckView *ui;
    std::vector<WorkingPackView *> workingPacks;
    std::vector<TargetPackView *> targetPacks;
    RemainingPackView * remainingPackView;
};

#endif // DECKVIEW_H
