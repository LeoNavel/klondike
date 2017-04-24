#include "remainingpackview.h"
#include "ui_remainingpackview.h"

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
//    setMouseTracking(true);


}

void RemainingPackView::nextCard() {
    CardStacks::RemainingPack::nextCard();
    update();
}

bool RemainingPackView::eventFilter(QObject *obj, QEvent *e) {
    if(obj == ui->frame && e->type() == QEvent::MouseButtonPress){
        if(!selectionDelegate->isEmpty())
            return false;
        if(allCardVisible()){
            turnPack();
            update();
        } else{
            nextCard();
            update();
        }
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
            QPixmap cursor_pixmap = selectionDelegate->grab();

            QCursor cursor_default = QCursor(cursor_pixmap, me->pos().x(), me->pos().y());
            QApplication::setOverrideCursor(cursor_default);
            update();
        } else {
            qDebug() << "chyba";
        }
        return true;
    }
    return QWidget::eventFilter(obj, e);
}


void RemainingPackView::initWithStack(CardStacks::GenericCardStack stack){
    GenericCardStack s1;
    while(!stack.isEmpty())
        s1.push(stack.topAndPop());
    while(!s1.isEmpty())
        RemainingPack::push(s1.topAndPop());
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


RemainingPackView::~RemainingPackView()
{
    delete ui;
}

