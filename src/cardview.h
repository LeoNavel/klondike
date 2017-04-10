#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QFrame>
#include "Card.hpp"
#include <QMouseEvent>


namespace Ui {
class CardView;
}

class CardView : public QFrame, card::Card
{
    Q_OBJECT
public:
    struct {
        int width = 125;
        int height = 175;
    } defaultSize;
    explicit CardView(QWidget *parent = 0);
    CardView(int value, card::sign sign, QWidget *parent = 0);
//    void setCard();
    void setGeometry(const QRect &r);
    void redrawCard();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    ~CardView();

private:
    Ui::CardView *ui;
//    int value = 1;
//    card::sign sign = card::sign::CLUBS;
    QPoint offset;

};

#endif // CARDVIEW_H
