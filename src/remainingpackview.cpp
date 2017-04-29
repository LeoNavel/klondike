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

//    this->

    ui->frame->installEventFilter(this);
    currentCardView->installEventFilter(this);
//    setMouseTracking(true);

//    for(int i = 0; i < 20; i++)
//        nextCard();

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
//        selectionDelegate->mainView->cont
//        if(allCardVisible()){
//            turnPack();
//            update();
//        } else{
//            nextCard();
//            update();
//        }
        return true;
    }
    if(obj == currentCardView && e->type() == QEvent::MouseButtonPress){
        if(selectionDelegate->isEmpty()){
            try{
                selectionDelegate->push(topAndPopCurrent());
            } catch (ErrorException err) {
                qDebug() << err.get_message().c_str();
            }
            QMouseEvent * me = static_cast<QMouseEvent*>(e);
            QPoint p = currentCardView->pos();
//            p = QPoint(p.x(), p.y());
            selectionDelegate->setGeometry(QRect(p,currentCardView->rect().size()));
            selectionDelegate->setSourcePack(this);
//            selectionDelegate->setGeometry(currentCardView->rect());
            selectionDelegate->raise();
            selectionDelegate->setOffset(me->pos());
            selectionDelegate->setWpv(false);
//            selectionDelegate->show();
//            QPixmap cursor_pixmap = selectionDelegate->grab();

//            QCursor cursor_default = QCursor(cursor_pixmap, me->pos().x(), me->pos().y());
//            QApplication::setOverrideCursor(cursor_default);
            selectionDelegate->mainView->updateCursor();
            update();
        } else {
//            selectionDelegate->rollBack();
//            selectionDelegate->clear();
//            QApplication::restoreOverrideCursor();
            return false;
        }
        return true;
    }
    return QWidget::eventFilter(obj, e);
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
            backCard->setStyleSheet("background-color: rgba(1,1,1,0);");
        } else {
            backCard->setStyleSheet("background-color: orange;");
        }
    } else {
        backCard->setStyleSheet("background-color: rgba(1,1,1,0);");
        currentCardView->hide();
    }
}



void RemainingPackView::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);
    currentCardView->setGeometry(QRect(QPoint((r.width() + 10)/2,0), QSize((r.width() - 10)/2,r.height())));

    backCard->setGeometry(QRect(QPoint(0,0), currentCardView->rect().size()));
}

void RemainingPackView::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton) {
        selectionDelegate->clear();
        selectionDelegate->mainView->requestUpdateAll();
        selectionDelegate->mainView->updateCursor();
//        if(!selectionDelegate->isEmpty()) {
//            selectionDelegate->rollBack();
//            selectionDelegate->clear();
//            QApplication::restoreOverrideCursor();
//        }
    }
}

RemainingPackView::~RemainingPackView()
{
    delete ui;
}

