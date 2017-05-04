/*! 
 *  \file       workingpackview.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
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
    if(e->type() == QEvent::MouseButtonPress){
        if(selectionDelegate->isEmpty()){
            CardStacks::GenericCardStack gs, gs1;
            bool found = false;
            if(cards.size() == 0)
                return false;
            CardView * lastCard = cards[cards.size() - 1];
            if(lastCard == obj && !lastCard->isTurnedUp()){
                selectionDelegate->mainView->turnCard(this);
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
                update();
                return true;
            }
        } else {
            return false;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void WorkingPackView::highlight(unsigned int count){
    if(cards.size() > 0){
    std::vector<std::string> css = std::vector<std::string>();
        for(unsigned int i = 0; i < count; i++){
            CardView * cv = cards[cards.size() - 1 -i];
            QString cssQstr = cv->styleSheet();
            css.push_back(cssQstr.toStdString());
            cv->setStyleSheet("background-color: #d00");
        }
        QTime dieTime= QTime::currentTime().addMSecs(250);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        for(unsigned int i = 0; i < count; i++){
            CardView * cv = cards[cards.size() - 1 -i];
            std::string cssStr = css[css.size() - 1];
            cv->setStyleSheet(cssStr.c_str());
            css.pop_back();
        }
    } else {
        QString css = this->styleSheet();
        setStyleSheet("background-color: #d00");
        QTime dieTime= QTime::currentTime().addMSecs(250);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        setStyleSheet(css);
    }
    update();
}

void WorkingPackView::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
        if(!selectionDelegate->isEmpty()){
            if(selectionDelegate->isWpv()){
                WorkingPackView *wpv = static_cast<WorkingPackView *>(selectionDelegate->getSourcePack());
                if(wpv != this)
                    selectionDelegate->mainView->moveCards(wpv, this, selectionDelegate->getSize());
                else{
                    selectionDelegate->mainView->requestUpdateAll();
                }
            } else {
                selectionDelegate->mainView->moveCardsFromRemainingPack(this);
            }
            selectionDelegate->clear();
            selectionDelegate->hide();
            selectionDelegate->mainView->updateCursor();
        }
    }
}

WorkingPackView::~WorkingPackView()
{
    delete ui;
}
