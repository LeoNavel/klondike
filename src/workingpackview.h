#ifndef WORKINGPACKVIEW_H
#define WORKINGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include <vector>
#include "cardview.h"
#include <QDebug>

namespace Ui {
class WorkingPackView;
}

class WorkingPackView : public QFrame, public CardStacks::WorkingPack
{
    Q_OBJECT

public:
    explicit WorkingPackView(QWidget *parent = 0);
    void setGeometry(const QRect &r);
    void push_invisible(card::Card card);
    void turn_invisible();
    ~WorkingPackView();

private:
    Ui::WorkingPackView *ui;
    std::vector<CardView *> cards;
};

#endif // WORKINGPACKVIEW_H
