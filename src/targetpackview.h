#ifndef TARGETPACKVIEW_H
#define TARGETPACKVIEW_H

#include <QFrame>
#include <QDebug>
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
    explicit TargetPackView(QWidget *parent = 0);
//    bool eventFilter(QObject *obj, QEvent *e);
    CardSelection * selectionDelegate;
    void mouseReleaseEvent(QMouseEvent *e);
    void setGeometry(const QRect &r);
    void paintEvent(QPaintEvent * e);
    void setTopCard(card::Card *card);
    ~TargetPackView();

private:
    Ui::TargetPackView *ui;
    CardView * currentCardView;
};

#endif // TARGETPACKVIEW_H
