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

void WorkingPackView::push(card::Card card) {
    WorkingPack::push(card);
    CardView * cv = new CardView(card.get_number(), card.get_sign(), this);
    cv->turnUp();
    cards.push_back(cv);
    update();
}

void WorkingPackView::turn_invisible() {
    WorkingPack::turn_invisible();
    CardView * c = cards[cards.size() - 1];
    c->turnUp();
}


void WorkingPackView::paintEvent(QPaintEvent *e){
    QWidget::paintEvent(e);
    int index = 0;

    QRect nr = this->rect();
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
        nr.setSize(this->rect().size());
        c->setGeometry(nr);

//        if(c->isTurnedUp())
        c->installEventFilter(this);
        c->show();
        index++;
    }
}

void WorkingPackView::pop() {
    WorkingPack::pop();
    CardView * c = cards[cards.size()-1];
    cards.pop_back();
    delete c;
}

bool WorkingPackView::eventFilter(QObject *obj, QEvent *e) {
    selectionDelegate->installEventFilter(this);
    if(e->type() == QEvent::MouseButtonPress){
        if(selectionDelegate->isEmpty()){

            CardStacks::GenericCardStack gs, gs1;
            bool found = false;
            if(cards.size() > 0){
                qDebug() << "mama";
                if(cards[cards.size() - 1] == obj && !cards[cards.size()-1]->isTurnedUp()){
                    turn_invisible();
                    update();
                    return true;
                }
            }



            found = false;
            QPoint cp;
            for(CardView * c:cards){
                if(obj == c){
                    if(!c->isTurnedUp())
                        return false;
                    cp = c->pos();
                    found = true;
                }
                if (found){
                    gs1.push(WorkingPack::topVisible());
                    pop();
                }
            }
            if(found){
                while(!gs1.isEmpty())
                    gs.push(gs1.topAndPop());
                qDebug() << gs.size();
                selectionDelegate->show();
                selectionDelegate->setStyleSheet("background-color: #ff0;");
                QMouseEvent * me = static_cast<QMouseEvent*>(e);
                QPoint p = this->pos();
                qDebug() << p;
                qDebug() << cp;
                p = QPoint(p.x(), p.y() + cp.y());
                qDebug() << p;
                selectionDelegate->setGeometry(QRect(p,QSize(130,300)));
                qDebug() << me->pos();
                selectionDelegate->push(gs);
//                selectionDelegate->update();
                selectionDelegate->raise();
                selectionDelegate->setSourcePack(this);
                selectionDelegate->setOffset(me->pos());

                update();
                return true;
            }
        } else {
//            qDebug() << "tato";

//            QMouseEvent * me = static_cast<QMouseEvent*>(e);
//            qDebug() << me->pos();
            QPoint ep = mapToGlobal(selectionDelegate->pos());
            ep.setX(ep.x() + 20);
            ep.setY(ep.y() + 20);
            QPoint p = mapToGlobal(pos());
//            qDebug() << ep;
//            qDebug() << p;
//            qDebug() << "rect " << rect();
//            qDebug() << "rec1 " << selectionDelegate->pos();
//            qDebug() << mapFrom(selectionDelegate, me->pos());
            if(ep.x() < p.x() || ep.y() < p.y() || ep.x() > p.x() + rect().width() || ep.y() > p.y() + rect().height())
                return false;
//            qDebug() << "mam to";
            CardStacks::GenericCardStack gs_p;
            gs_p = selectionDelegate->getAll();
            try {
                push(gs_p.top());
            } catch (ErrorException err) {
                qDebug() << err.get_message().c_str();
                selectionDelegate->rollBack();
//            } catch (char const* err) {
//                qDebug() << err;
            }
            selectionDelegate->clear();
            selectionDelegate->hide();
//            selectionDelegate->update();
//            update();
//            repaint();
            return true;

        }
    }
    return QWidget::eventFilter(obj, e);
}

WorkingPackView::~WorkingPackView()
{
    delete ui;
}