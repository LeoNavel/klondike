#ifndef REMAININGPACKVIEW_H
#define REMAININGPACKVIEW_H

#include <QFrame>
#include "CardStacks.hpp"
#include <QDebug>

namespace Ui {
class RemainingPackView;
}

class RemainingPackView : public QFrame, public CardStacks::RemainingPack
{
    Q_OBJECT

public:
    explicit RemainingPackView(QWidget *parent = 0);
    ~RemainingPackView();

private:
    Ui::RemainingPackView *ui;
};

#endif // REMAININGPACKVIEW_H
