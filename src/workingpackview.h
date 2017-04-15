#ifndef WORKINGPACKVIEW_H
#define WORKINGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include <vector>
#include "cardview.h"
#include "cardselection.h"
#include <QDebug>
#include "Error.hpp"

namespace Ui {
class WorkingPackView;
}

class WorkingPackView : public QFrame, public CardStacks::WorkingPack
{
    Q_OBJECT

public:
    explicit WorkingPackView(QWidget *parent = 0);
    void push_invisible(card::Card card);
    void turn_invisible();
    bool eventFilter(QObject *obj, QEvent *e);
    void paintEvent(QPaintEvent *e);
    void pop();
    void push(card::Card card);
    CardSelection * selectionDelegate;
    ~WorkingPackView();

private:
    Ui::WorkingPackView *ui;
    std::vector<CardView *> cards;
};

#endif // WORKINGPACKVIEW_H
