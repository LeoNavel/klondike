/*! 
 *  \file       remainingpackview.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "remainingpackview.h"
#include "ui_remainingpackview.h"
#include "deckview.h"

RemainingPackView::RemainingPackView(QWidget *parent) :
    QFrame(parent),
    CardStacks::RemainingPack(),
    ui(new Ui::RemainingPackView)
{

    ui->setupUi(this);
    this->backCard = ui->frame;
    backCard->setStyleSheet("background-color: rgba(1,1,1,0);");
    this->currentCardView = new CardView(1, card::sign::CLUBS, this);
    this->currentCardView->turnUp();

    ui->frame->installEventFilter(this);
    currentCardView->installEventFilter(this);
}

void RemainingPackView::nextCard() {
    selectionDelegate->mainView->getNext();
    update();
}

void RemainingPackView::turnPack(){
    selectionDelegate->mainView->turnRemainingCards();
    update();
}

bool RemainingPackView::eventFilter(QObject *obj, QEvent *e) {
    if(obj == ui->frame && e->type() == QEvent::MouseButtonPress){
        if(!selectionDelegate->isEmpty())
            return false;
        if(isEmpty())
            return false;
        if(!allCardVisible()){
            nextCard();
        } else {
            turnPack();
        }
        return true;
    }
    if(obj == currentCardView && e->type() == QEvent::MouseButtonPress){
        if(selectionDelegate->isEmpty()){
            try{
                selectionDelegate->push(topAndPopCurrent());
            } catch (ErrorException err) {
            }
            QMouseEvent * me = static_cast<QMouseEvent*>(e);
            QPoint p = currentCardView->pos();
            selectionDelegate->setGeometry(QRect(p,currentCardView->rect().size()));
            selectionDelegate->setSourcePack(this);
            selectionDelegate->raise();
            selectionDelegate->setOffset(me->pos());
            selectionDelegate->setWpv(false);
            selectionDelegate->mainView->updateCursor();
            update();
        } else {
            return false;
        }
        return true;
    }
    return QWidget::eventFilter(obj, e);
}

void RemainingPackView::highlightNextCardCommand(){
    QString ss = backCard->styleSheet();
    backCard->setStyleSheet("background-color: #d00;");
    QTime dieTime= QTime::currentTime().addMSecs(250);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    backCard->setStyleSheet(ss);
    update();
}

void RemainingPackView::highlightMove(){
    QString ss = currentCardView->styleSheet();
    currentCardView->setStyleSheet("background-color: #d00;");
    QTime dieTime= QTime::currentTime().addMSecs(250);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    currentCardView->setStyleSheet(ss);
    update();
}

void RemainingPackView::initWithStack(CardStacks::RemainingPack *stack){
    while(isSetCurrent()){
        popCurrent();
    }
    while(!isEmpty())
        pop();

    if(stack->isEmpty()){

    } else {
        for(unsigned int i = 0; i < stack->size(); i++){
            card::Card c = (*stack)[i];
            push(c);
        }
        if(stack->isSetCurrent()){
            do{
                RemainingPack::nextCard();
            }while(stack->currentCard() != currentCard());
        }
    }
    if(allCardVisible()){
        backCard->setStyleSheet("background-color: rgba(1,1,1,0);");
    } else {
        backCard->setStyleSheet("background-color: orange;");
    }

    update();
}

void RemainingPackView::paintEvent(QPaintEvent *e){
    QFrame::paintEvent(e);
    if(!RemainingPack::isEmpty()) {
        if(isSetCurrent()) {
            currentCardView->show();
            currentCardView->set_number(currentCard().get_number());
            currentCardView->set_sign(currentCard().get_sign());
        } else {
            currentCardView->hide();
        }
        if(allCardVisible()) {
//            QString clr = (highlightedBackCard)?"#d00":"rgba(1,1,1,0)";
//            backCard->setStyleSheet("background-color: " + clr + ";");
        } else {
//            QString clr = (highlightedBackCard)?"#d00":"orange";
//            backCard->setStyleSheet("background-color: " + clr +";");
        }
    } else {
//        QString clr = (highlightedBackCard)?"#d00":"rgba(1,1,1,0)";
//        backCard->setStyleSheet("background-color: " + clr + ";");
        currentCardView->hide();
    }
}



void RemainingPackView::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);
    currentCardView->setGeometry(QRect(QPoint((r.width() + 10)/2,0), QSize((r.width() - 10)/2,r.height())));

    backCard->setGeometry(QRect(QPoint(0,0), currentCardView->rect().size()));
    QRect nr = QRect(r.x(), r.y(), (r.width() + 10)/2 + currentCardView->rect().width(), currentCardView->rect().height());
    QFrame::setGeometry(nr);
}

void RemainingPackView::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
        selectionDelegate->clear();
        selectionDelegate->mainView->requestUpdateAll();
        selectionDelegate->mainView->updateCursor();
    }
}

RemainingPackView::~RemainingPackView()
{
    delete ui;
}

