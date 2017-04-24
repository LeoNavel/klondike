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

namespace Ui {
class DeckView;
}

class DeckView : public QFrame
{
    Q_OBJECT

public:
    explicit DeckView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    void prepareDeck(unsigned char shuffles);
    CardSelection * cardSelection;
    ~DeckView();

private:
    Ui::DeckView *ui;
    std::vector<WorkingPackView *> workingPacks;
    std::vector<TargetPackView *> targetPacks;
};

#endif // DECKVIEW_H
