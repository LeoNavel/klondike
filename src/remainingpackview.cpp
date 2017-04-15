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
//    setMouseTracking(true);


}

void RemainingPackView::nextCard() {
    CardStacks::RemainingPack::nextCard();
    redraw();
}

bool RemainingPackView::eventFilter(QObject *obj, QEvent *e) {
    if(obj == ui->frame && e->type() == QEvent::MouseButtonPress){
        if(allCardVisible()){
            turnPack();
            redraw();
        } else
            nextCard();
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
    redraw();
}

void RemainingPackView::redraw() {
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

