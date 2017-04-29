#include "workingpackview.h"
#include "ui_workingpackview.h"
#include "deckview.h"
WorkingPackView::WorkingPackView(QWidget *parent) :
    QFrame(parent),
    WorkingPack(),
    ui(new Ui::WorkingPackView)
{
    ui->setupUi(this);
}


void WorkingPackView::setCards(CardStacks::GenericCardStack stack){
    for(auto c: cards)
        delete c;
    cards.clear();
    for(int i = 0; i < stack.size(); i++){
        card::Card c = stack[i];
        CardView *cv = new CardView(c.get_number(), c.get_sign(), this);
        if(c.isTurnedUp())
            cv->turnUp();

        cv->installEventFilter(this);
        cv->show();
        cards.push_back(cv);
    }
    update();
}

void WorkingPackView::push_invisible(card::Card card) {
//    WorkingPack::push_invisible(card);
    cards.push_back(new CardView(card.get_number(), card.get_sign(), this));
}

void WorkingPackView::push(card::Card card) {
//    WorkingPack::push(card);
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
        index++;
    }
}

void WorkingPackView::pop() {
//    WorkingPack::pop();
    CardView * c = cards[cards.size()-1];
    cards.pop_back();
    delete c;
}

bool WorkingPackView::eventFilter(QObject *obj, QEvent *e) {
//    selectionDelegate->installEventFilter(this);
    if(e->type() == QEvent::MouseButtonPress){
        if(selectionDelegate->isEmpty()){
            qDebug() << "sata";
            CardStacks::GenericCardStack gs, gs1;
            bool found = false;
            if(cards.size() == 0)
                return false;
            CardView * lastCard = cards[cards.size() - 1];
            if(lastCard == obj && !lastCard->isTurnedUp()){
                selectionDelegate->mainView->turnCard(this);
//                    turn_invisible();
//                    update();
                return true;
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
                    CardView * topCard = cards[cards.size() - 1];
                    card::Card leCard = card::Card(topCard->get_number(), topCard->get_sign(), true);
                    gs1.push(leCard);
                    cards.pop_back();
                    delete topCard;
                }
            }
            if(found){
                while(!gs1.isEmpty())
                    gs.push(gs1.topAndPop());
//                selectionDelegate->show();
                QMouseEvent * me = static_cast<QMouseEvent*>(e);

                selectionDelegate->push(gs);
                QPoint p = this->pos();
                p = QPoint(p.x(), p.y() + cp.y());
                selectionDelegate->setGeometry(QRect(p, QWidget::size()));
                selectionDelegate->raise();
                selectionDelegate->setSourcePack(this);
                selectionDelegate->setOffset(me->pos());
                selectionDelegate->setWpv(true);

                selectionDelegate->mainView->updateCursor();

//                QPixmap cursor_pixmap = selectionDelegate->grab();
//                QCursor cursor_default = QCursor(cursor_pixmap, me->pos().x(), me->pos().y());
//                QApplication::setOverrideCursor(cursor_default);

                update();
                return true;
            }
        } else {
            return false;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void WorkingPackView::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
        if(!selectionDelegate->isEmpty()){
            if(selectionDelegate->isWpv()){
                WorkingPackView *wpv = static_cast<WorkingPackView *>(selectionDelegate->getSourcePack());
                selectionDelegate->mainView->moveCards(wpv, this, selectionDelegate->getSize());
            } else {
                selectionDelegate->mainView->moveCardsFromRemainingPack(this);
            }
//            std::vector<card::Card> gs_p;
//            gs_p = selectionDelegate->getAll();
//            try {
//                for(auto c:gs_p)
//                    push(c);
//            } catch (ErrorException err) {
//                qDebug() << err.get_message().c_str();
//                selectionDelegate->rollBack();
//                update();
////            } catch (char const* err) {
////                qDebug() << err;
//            }
            selectionDelegate->clear();
            selectionDelegate->hide();
//            selectionDelegate->update();
//            update();
//            repaint();
//            QApplicati
//            on::restoreOverrideCursor();
            selectionDelegate->mainView->updateCursor();
//            return true;
//            return true;
        }
    }
}

WorkingPackView::~WorkingPackView()
{
    delete ui;
}
