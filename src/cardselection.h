/*! 
 *  \file       cardselection.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               2.05.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         card selection
 *
 ***************************************/

#ifndef CARDSELECTION_H
#define CARDSELECTION_H

#include <QFrame>
#include <vector>
#include "CardStacks.hpp"
#include "cardview.h"
class DeckView;
namespace Ui {
class CardSelection;
}

class CardSelection : public QFrame
{
    Q_OBJECT

public:
    /**
     * construct card selection
     *
     * @param parent parent widget
     * @return card selection
     */
    explicit CardSelection(QWidget *parent = 0);

    /**
     * set geometry for selection
     *
     * @param r rectangle
     */
    void setGeometry(const QRect &r);

    /**
     * paint event
     *
     * @param e event
     */
    void paintEvent(QPaintEvent * e);

    /**
     * clear selection
     */
    void clear();

    /**
     * @return true if slelection is empty
     */
    bool isEmpty();

    /**
     * set source pack
     *
     * @param wpv source pack
     */
    void setSourcePack(void * wpv);

    /**
     * push one card
     *
     * @param c card
     */
    void push(card::Card c);

    /**
     * push card stack
     *
     * @param stack card stack
     */
    void push(CardStacks::GenericCardStack stack);

    /**
     * @return all cards
     */
    std::vector<card::Card> getAll();

    /**
     * set offset for mouse pointer
     *
     * @param p point
     */
    void setOffset(QPoint p);

    /**
     * roll back all changes
     */
    void rollBack();

    /**
     * set true if source pack is WorkingPackView
     */
    void setWpv(bool);

    /**
     * indicates that source pack is WorkingPackView
     *
     * @return true if source pack is WorkingPackView
     */
    bool isWpv();

    /**
     * @return source pack
     */
    void * getSourcePack();

    /**
     * @return size of selection
     */
    unsigned int getSize();

    /**
     * @return offset
     */
    QPoint getOffset();

    /**
     * main view
     */
    DeckView * mainView = nullptr;

    /**
     * set main view
     *
     * @param mainView main view
     */
    void setMainView(DeckView *mainView);
    ~CardSelection();

private:
    Ui::CardSelection *ui;
    QPoint offset;
    void * sourcePack;
    bool wpv;
    std::vector<CardView *> cards;
};

#endif // CARDSELECTION_H
