/*! 
 *  \file       deckview.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "deckview.h"
#include "ui_deckview.h"
#include "cardview.h"

DeckView::DeckView(QWidget *parent) :
    QFrame(parent),
    GenericView(),
    ui(new Ui::DeckView)
{
    ui->setupUi(this);

    this->cardSelection = new CardSelection(this);
    cardSelection->setMainView(this);
    cardSelection->hide();

    remainingPackView = new RemainingPackView(this);
    remainingPackView->selectionDelegate = cardSelection;
    remainingPackView->show();

    for(int i = 0; i < 4; i++){
        TargetPackView *tpv = new TargetPackView(this);
        tpv->selectionDelegate = cardSelection;
        tpv->show();
        targetPacks.push_back(tpv);
    }

    for(int i = 0; i < 7; i++){
        WorkingPackView * wpv = new WorkingPackView(this);
        wpv->selectionDelegate = cardSelection;
        wpv->show();
        workingPacks.push_back(wpv);
    }

//    setCursor(Qt::ClosedHandCursor);
    QFrame::update();
}

void DeckView::getNext(){
    controller->get_next();
}
void DeckView::turnRemainingCards(){
    controller->roll_rem_pack();
}

void DeckView::updateCursor(){
    QCursor newCursor;
    if(cardSelection->getSize() > 0){
        QPixmap cursor_pixmap = cardSelection->grab();
        QPoint me = cardSelection->getOffset();
        newCursor = QCursor(cursor_pixmap, me.x(), me.y());
    } else {
        newCursor = Qt::ArrowCursor;
    }
//    QApplication::setOverrideCursor(cursor_default);
    setCursor(newCursor);
}

void DeckView::moveCardsFromRemainingPack(WorkingPackView *to){
    cmd_t cmd;
    stack_id_t dest;
    stack_id_t src;

    src.type_stack = REMAINING_STACK;
    src.id_stack = 0;

    dest.type_stack = WORKING_STACK;
    int i = 0;
    for(WorkingPackView *wpv: workingPacks){
        if(wpv == to)
            break;
        i++;
    }
    dest.id_stack = i;

    cmd.num_of_cards = 1;
    cmd.source_stack = src;
    cmd.destination_stack = dest;
    controller->move_card(cmd);
}

void DeckView::moveCardsFromRemainingPack(TargetPackView *to){
    cmd_t cmd;
    stack_id_t dest;
    stack_id_t src;

    src.type_stack = REMAINING_STACK;
    src.id_stack = 0;

    dest.type_stack = TARGET_STACK;
    int i = 0;
    for(TargetPackView *tpv: targetPacks){
        if(tpv == to)
            break;
        i++;
    }
    dest.id_stack = i;

    cmd.num_of_cards = 1;
    cmd.source_stack = src;
    cmd.destination_stack = dest;
    controller->move_card(cmd);
}

void DeckView::moveCardsToTargetPack(WorkingPackView *from, TargetPackView *to, unsigned int count){
    cmd_t cmd;
    stack_id_t dest;
    stack_id_t src;

    src.type_stack = WORKING_STACK;
    int i = 0;
    for(WorkingPackView *wpv: workingPacks){
        if(wpv == from)
            break;
        i++;
    }
    src.id_stack = i;

    dest.type_stack = TARGET_STACK;
    i = 0;
    for(TargetPackView *tpv: targetPacks){
        if(tpv == to)
            break;
        i++;
    }

    dest.id_stack = i;

    cmd.num_of_cards = count;
    cmd.source_stack = src;
    cmd.destination_stack = dest;
    controller->move_card(cmd);
}

void DeckView::moveCards(WorkingPackView *from, WorkingPackView *to, unsigned int count){
    cmd_t cmd;
    stack_id_t dest;
    stack_id_t src;

    src.type_stack = WORKING_STACK;
    int i = 0;
    for(WorkingPackView *wpv: workingPacks){
        if(wpv == from)
            break;
        i++;
    }
    src.id_stack = i;

    dest.type_stack = WORKING_STACK;
    i = 0;
    for(WorkingPackView *wpv: workingPacks){
        if(wpv == to)
            break;
        i++;
    }
    dest.id_stack = i;

    cmd.num_of_cards = (signed) count;
    cmd.source_stack = src;
    cmd.destination_stack = dest;
    controller->move_card(cmd);
}

void DeckView::update(CardStacks::RemainingPack *remainigPack) {
    remainingPackView->initWithStack(remainigPack);
//    QFrame::update();
}

void DeckView::update(int id, card::Card *topTargetCard){
    TargetPackView * tpv = targetPacks[id];
    tpv->setTopCard(topTargetCard);
}

void DeckView::update(int id, CardStacks::GenericCardStack workingPack){
    WorkingPackView * wpv = workingPacks[id];
    wpv->setCards(workingPack);
}

void DeckView::requestUpdateAll() {
    controller->updateAll();
}

//DeckView::DeckView(Controller *controller, QWidget *parent):
//    QFrame(parent),
//    GenericView(controller),
//    ui(new Ui::DeckView)
//{
//    ui->setupUi(this);


//}

//void DeckView::prepareDeck(unsigned char shuffles) {
//    CardStacks::CardDeck cardDeck = CardStacks::CardDeck();

//    for(int i = 0; i < shuffles; i++)
//        cardDeck.shuffleCards();

//    for(int i = 0; i < 7; i++){
//        WorkingPackView * nwpv = new WorkingPackView(this);
//        nwpv->selectionDelegate = cardSelection;
//        workingPacks.push_back(nwpv);
//        for(int j = 0; j < i; j++)
//            workingPacks[i]->push_invisible(cardDeck.topAndPop());

//        workingPacks[i]->push_invisible(cardDeck.topAndPop());
//        workingPacks[i]->turn_invisible();

////        cardSelection->installEventFilter(workingPacks[i]);
//    }


//    ui->remainingCards->initWithStack(cardDeck);
//    ui->remainingCards->selectionDelegate = cardSelection;

//    for(int i = 0; i < 4; i++) {
//        TargetPackView * tpv = new TargetPackView(this);
//        tpv->selectionDelegate = cardSelection;
//        targetPacks.push_back(tpv);
//    }
//}

void DeckView::turnCard(WorkingPackView *on){
    int i = 0;
    for(WorkingPackView * wpv:workingPacks){
        if(wpv == on)
            break;
        i++;
    }
    controller->turn_card(i);
}

void DeckView::resizeEvent(QResizeEvent* event)
{
   QFrame::resizeEvent(event);
   QSize size = event->size();
   QRect ar = remainingPackView->rect();
   ar.setTopLeft(QPoint(5, 5));
   QRect nr = QRect(ar.topLeft(), QSize((size.width() / 7) * 2 + 10, size.height() / 4));
   remainingPackView->setGeometry(nr);

   int index = 0;
   for(TargetPackView * pack: targetPacks){
       int pw = size.width() / 7;
       QRect npr = QRect(size.width() - 5 - index * (pw + 10) - pw, 5, pw, size.height() / 4);
       pack->setGeometry(npr);
       index++;
   }

   index = 0;
   int wid = (size.width() / 7) - 5;
   QPoint newTopLeft = nr.bottomLeft();
   newTopLeft.setY(newTopLeft.y() + 10);
   for(WorkingPackView * pack: workingPacks){
       newTopLeft.setX(nr.x() + (wid + 5) * index);
       pack->setGeometry(QRect(newTopLeft,QSize(wid, ((size.height() / 4) * 3 - 20))));
       index++;
   }
}

void DeckView::highlightNextCardCommand(){
    remainingPackView->highlightNextCardCommand();
}

void DeckView::highlightRemainingToWorking(unsigned int id){
    remainingPackView->highlightMove();
    WorkingPackView * wpv = workingPacks[id];
    wpv->highlight(1);
}

void DeckView::highlightRemainingToTarget(unsigned int id){
    remainingPackView->highlightMove();
    TargetPackView * tpv = targetPacks[id];
    tpv->highlight();
}

void DeckView::highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID){
    WorkingPackView * wpv = workingPacks[workingDeckID];
    wpv->highlight(1);
    TargetPackView * tpv = targetPacks[targetDeckID];
    tpv->highlight();
}

void DeckView::highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID){
    WorkingPackView *wpv = workingPacks[sourceID];
    wpv->highlight(count);

    wpv = workingPacks[destinationID];
    wpv->highlight(1);
}

void DeckView::finishGame(){
    cardSelection->clear();
    updateCursor();
    QRect r = targetPacks[0]->rect();
    QPoint p = targetPacks[0]->pos();
    TargetPackView * tpw = targetPacks[0];
    card::sign s = tpw->getColor();
    int j = 13;
    for(int x = p.x(); x > - 50; x-=20){
        if(j == 0)
            j = 13;
        CardView * c = new CardView(j, s, this);
        int y = p.y() + ( - x + p.x()) * (- x + p.x()) / 1000;
        c->setGeometry(r);
        c->move(x, y);
        c->show();
        c->turnUp();
        finishGameCards.push_back(c);
        QTime dieTime= QTime::currentTime().addMSecs(25);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        j--;
    }

    r = targetPacks[3]->rect();
    p = targetPacks[3]->pos();
    s = targetPacks[3]->getColor();
    j = 13;
    for(int x = p.x(); x < this->width() + 50; x+=20){
        if(j == 0)
            j = 13;
        CardView * c = new CardView(j, s, this);
        int y = p.y() + ( - x + p.x()) * ( - x + p.x()) / 1000;
        c->setGeometry(r);
        c->move(x, y);
        c->show();
        c->turnUp();
        finishGameCards.push_back(c);
        QTime dieTime= QTime::currentTime().addMSecs(25);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        j--;
    }

    r = targetPacks[1]->rect();
    p = targetPacks[1]->pos();
    s = targetPacks[1]->getColor();
    j = 13;
    for(int x = p.x(); x > - 100; x-=20){
        if(j == 0)
            j = 13;
        CardView * c = new CardView(j, s, this);
        int y = p.y() + ( - x + p.x()) * (- x + p.x()) / 5000;
        c->setGeometry(r);
        c->move(x, y);
        c->show();
        c->turnUp();
        finishGameCards.push_back(c);
        QTime dieTime= QTime::currentTime().addMSecs(25);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        j--;
    }

    r = targetPacks[2]->rect();
    p = targetPacks[2]->pos();
    s = targetPacks[2]->getColor();
    j = 13;
    for(int x = p.x(); x < this->width() + 50; x+=20){
        if(j == 0)
            j = 13;
        CardView * c = new CardView(j, s, this);
        int y = p.y() + ( - x + p.x()) * ( - x + p.x()) / 100;
        c->setGeometry(r);
        c->move(x, y);
        c->show();
        c->turnUp();
        finishGameCards.push_back(c);
        QTime dieTime= QTime::currentTime().addMSecs(25);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        j--;
    }


    r = targetPacks[0]->rect();
    p = targetPacks[0]->pos();
    s = targetPacks[0]->getColor();
    j = 13;
    for(int x = p.x(); x > - 50; x-=20){
        if(j == 0)
            j = 13;
        CardView * c = new CardView(j, s, this);
        int y = p.y() + ( - x + p.x()) * (- x + p.x()) / 250;
        c->setGeometry(r);
        c->move(x, y);
        c->show();
        c->turnUp();
        finishGameCards.push_back(c);
        QTime dieTime= QTime::currentTime().addMSecs(25);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        j--;
    }

}

void DeckView::restartView(){
    for(auto c: finishGameCards)
        delete c;
}

DeckView::~DeckView()
{
    delete ui;
    for(auto wp: workingPacks)
        delete wp;
    for(auto tp: targetPacks)
        delete tp;
    for(auto c: finishGameCards)
        delete c;
    delete remainingPackView;
}
