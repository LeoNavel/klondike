/*! 
 *  \file       workingpackview.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef WORKINGPACKVIEW_H
#define WORKINGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include <vector>
#include "cardview.h"
#include "cardselection.h"
#include "Error.hpp"

namespace Ui {
class WorkingPackView;
}

class WorkingPackView : public QFrame, public CardStacks::WorkingPack
{
    Q_OBJECT

public:
    /**
     * construct view represention of working pack
     *
     * @param parent parenting view
     * @return new object
     */
    explicit WorkingPackView(QWidget *parent = 0);

    /**
     * push invisible card
     *
     * @param card card
     */
    void push_invisible(card::Card card);

    /**
     * turn invisible card
     */
    void turn_invisible();

    /**
     * event filter
     *
     * @param obj sender
     * @param e event
     * @return if we are interested in current evet
     */
    bool eventFilter(QObject *obj, QEvent *e);

    /**
     * painting
     *
     * @param e event
     */
    void paintEvent(QPaintEvent *e);

    /**
     * pop card
     */
    void pop();

    /**
     * push card
     *
     * @param card card
     */
    void push(card::Card card);
    CardSelection * selectionDelegate;

    /**
     * set cards
     *
     * @param stack data
     */
    void setCards(CardStacks::GenericCardStack stack);

    /**
     * checking for move completion
     *
     * @param e event
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * highlight cards
     *
     * @param count number of cards
     */
    void highlight(unsigned int count);
    ~WorkingPackView();

private:
    Ui::WorkingPackView *ui;
    std::vector<CardView *> cards;
};

#endif // WORKINGPACKVIEW_H
