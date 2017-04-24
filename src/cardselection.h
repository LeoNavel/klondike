#ifndef CARDSELECTION_H
#define CARDSELECTION_H

#include <QFrame>
#include <vector>
#include "CardStacks.hpp"
#include "cardview.h"
#include <QDebug>

namespace Ui {
class CardSelection;
}

class CardSelection : public QFrame
{
    Q_OBJECT

public:
    explicit CardSelection(QWidget *parent = 0);
    void setGeometry(const QRect &r);
    void paintEvent(QPaintEvent * e);
    void clear();
    bool isEmpty();
    void setSourcePack(void * wpv);
    void push(card::Card c);
    void push(CardStacks::GenericCardStack stack);
    std::vector<card::Card> getAll();
    void setOffset(QPoint p);
    void mouseMoveEvent(QMouseEvent *event);
    void rollBack();
    void setWpv(bool);
    QPoint getOffset();
//    void mousePressEvent(QMouseEvent * event);
    ~CardSelection();

private:
    Ui::CardSelection *ui;
    QPoint offset;
    void * sourcePack;
    bool wpv;
    std::vector<CardView *> cards;
};

#endif // CARDSELECTION_H
