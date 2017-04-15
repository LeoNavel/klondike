#ifndef REMAININGPACKVIEW_H
#define REMAININGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include "cardview.h"
#include <QSignalTransition>
#include <QDebug>

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
    void redraw();
    void nextCard();
    ~RemainingPackView();



private:
    Ui::RemainingPackView *ui;
    QFrame * backCard;
    CardView * currentCardView;
};

#endif // REMAININGPACKVIEW_H
