#ifndef REMAININGPACKVIEW_H
#define REMAININGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include "cardview.h"
#include <QSignalTransition>
#include <QDebug>
#include "cardselection.h"
#include "Error.hpp"
#include <vector>

namespace Ui {
class RemainingPackView;
}

class RemainingPackView : public QFrame, public CardStacks::RemainingPack
{
    Q_OBJECT

public:
    explicit RemainingPackView(QWidget *parent = 0);
    void initWithStack(CardStacks::GenericCardStack stack);
    void setGeometry(const QRect &r);
    bool eventFilter(QObject *obj, QEvent *e);
    void paintEvent(QPaintEvent *e);
    void nextCard();
    CardSelection * selectionDelegate;
    ~RemainingPackView();



private:
    Ui::RemainingPackView *ui;
    QFrame * backCard;
//    CardView * getCurrentCardView();
    CardView * currentCardView;
//    std::vector<CardView *> turnedCards;
};

#endif // REMAININGPACKVIEW_H
