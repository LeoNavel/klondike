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
    void getNext();
    void turnRemainingCards();
    void moveCards(RemainingPackView *from, TargetPackView * to, int count);
    ~DeckView();

private:
    Ui::DeckView *ui;
    std::vector<WorkingPackView *> workingPacks;
    std::vector<TargetPackView *> targetPacks;
    RemainingPackView * remainingPackView;
};

#endif // DECKVIEW_H
