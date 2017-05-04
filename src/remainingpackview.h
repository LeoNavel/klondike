/*! 
 *  \file       remainingpackview.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef REMAININGPACKVIEW_H
#define REMAININGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include "cardview.h"
#include <QSignalTransition>
#include "cardselection.h"
#include "Error.hpp"
#include <QTime>
#include <vector>

namespace Ui {
class RemainingPackView;
}

class RemainingPackView : public QFrame, public CardStacks::RemainingPack
{
    Q_OBJECT

public:
    /**
     * construct view representation of remaining deck view
     *
     * @param parent parenting widget
     * @return new object
     */
    explicit RemainingPackView(QWidget *parent = 0);

    /**
     * init view with stack
     *
     * @param stack remaining pack
     */
    void initWithStack(CardStacks::RemainingPack *stack);

    /**
     * set geometry
     *
     * @param r rectangle
     */
    void setGeometry(const QRect &r);

    /**
     * check for move
     * @param obj sender
     * @param e event
     * @return true if we are interested in event
     */
    bool eventFilter(QObject *obj, QEvent *e);

    /**
     * paint
     *
     * @param e event
     */
    void paintEvent(QPaintEvent *e);

    /**
     * check for move completition
     * @param e event
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * get next card
     */
    void nextCard();

    /**
     * turn pack
     */
    void turnPack();

    /**
     * highlight next card move
     */
    void highlightNextCardCommand();

    /**
     * highlight move
     */
    void highlightMove();
    CardSelection * selectionDelegate;
    ~RemainingPackView();



private:
    Ui::RemainingPackView *ui;
    QFrame * backCard;
//    CardView * getCurrentCardView();
    CardView * currentCardView;
    CardView * previousCard;
//    std::vector<CardView *> turnedCards;
};

#endif // REMAININGPACKVIEW_H
