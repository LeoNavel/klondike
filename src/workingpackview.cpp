#include "workingpackview.h"
#include "ui_workingpackview.h"

WorkingPackView::WorkingPackView(QWidget *parent) :
    QFrame(parent),
    WorkingPack(),
    ui(new Ui::WorkingPackView)
{
    ui->setupUi(this);

}


void WorkingPackView::push_invisible(card::Card card) {
    WorkingPack::push_invisible(card);
    cards.push_back(new CardView(card.get_number(), card.get_sign(), this));
}

void WorkingPackView::turn_invisible() {
    WorkingPack::turn_invisible();
    CardView * c = cards[cards.size() - 1];
    c->turnUp();
}


void WorkingPackView::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);
    int index = 0;

    QRect nr = r;
    nr.setY(0);
    for(CardView * c: cards) {
        if(index == 0)
            nr.setTopLeft(QPoint(0, 0));
        else {
            if(cards[index-1]->isTurnedUp()){
                if(cards.size() > 17)
                    nr.setTopLeft(QPoint(0, 19 + nr.y()));
                else if (cards.size() > 10)
                    nr.setTopLeft(QPoint(0, 20 + nr.y()));
                else
                    nr.setTopLeft(QPoint(0, 25 + nr.y()));

            } else {
                if(cards.size() > 17)
                    nr.setTopLeft(QPoint(0, 1 + nr.y()));
                else if (cards.size() > 15)
                    nr.setTopLeft(QPoint(0, 3 + nr.y()));
                else if (cards.size() > 10)
                    nr.setTopLeft(QPoint(0, 10 + nr.y()));
                else if (cards.size() > 7)
                    nr.setTopLeft(QPoint(0, 20 + nr.y()));
                else
                    nr.setTopLeft(QPoint(0, 25 + nr.y()));
            }
        }

        nr.setSize(r.size());
        c->setGeometry(nr);
        index++;
    }
}

WorkingPackView::~WorkingPackView()
{
    delete ui;
}
