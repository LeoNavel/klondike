#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QFrame>
#include "Card.hpp"

namespace Ui {
class CardView;
}

class CardView : public QFrame
{
    Q_OBJECT
public:
    struct {
        int width = 125;
        int height = 175;
    } defaultSize;

public:
    explicit CardView(QWidget *parent = 0);
    void setGeometry(const QRect &r);
    ~CardView();

private:
    Ui::CardView *ui;
    int value = 1;
    card::sign sign = card::sign::CLUBS;
};

#endif // CARDVIEW_H
