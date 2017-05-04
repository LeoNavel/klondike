/*! 
 *  \file       targetpackview.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef TARGETPACKVIEW_H
#define TARGETPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include "cardselection.h"
#include "Error.hpp"
#include "cardview.h"

namespace Ui {
class TargetPackView;
}

class TargetPackView : public QFrame, public CardStacks::TargetPack
{
    Q_OBJECT

public:
    /**
     * construct view representaion of target pack
     *
     * @param parent parenting widget
     * @return new object
     */
    explicit TargetPackView(QWidget *parent = 0);

    CardSelection * selectionDelegate;

    /**
     * check for move completition
     *
     * @param e event
     */
    void mouseReleaseEvent(QMouseEvent *e);

    /**
     * set geometry
     *
     * @param r rectangle
     */
    void setGeometry(const QRect &r);

    /**
     * set top card
     *
     * @param card card
     */
    void setTopCard(card::Card *card);

    /**
     * @return sign of card
     */
    card::sign getColor();
    ~TargetPackView();

    /**
     * highlight top card
     */
    void highlight();

private:
    Ui::TargetPackView *ui;
    CardView * currentCardView;
};

#endif // TARGETPACKVIEW_H
