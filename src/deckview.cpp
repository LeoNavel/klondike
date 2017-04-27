#include "deckview.h"
#include "ui_deckview.h"
#include "cardview.h"
#include <QDebug>

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

}

void DeckView::getNext(){
    controller->get_next();
}
void DeckView::turnRemainingCards(){
    controller->roll_rem_pack();
}

void DeckView::update(CardStacks::RemainingPack *remainigPack) {
    remainingPackView->initWithStack(remainigPack);
    qDebug() << "som tuta";
    QFrame::update();
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

void DeckView::resizeEvent(QResizeEvent* event)
{
   QFrame::resizeEvent(event);
   QSize size = event->size();
   QRect ar = remainingPackView->rect();
   ar.setTopLeft(QPoint(5, 5));
   QRect nr = QRect(ar.topLeft(), QSize((size.width() / 7) * 2 + 10, size.height() / 4));
   remainingPackView->setGeometry(nr);

//   int index = 0;
//   for(TargetPackView * pack: targetPacks){
//       int pw = size.width() / 7;
//       QRect npr = QRect(size.width() - 5 - index * (pw + 10) - pw, 5, pw, size.height() / 4);
//       pack->setGeometry(npr);
//       index++;
//   }



//   index = 0;
//   int wid = (size.width() / 7) - 5;
//   QPoint newTopLeft = nr.bottomLeft();
//   newTopLeft.setY(newTopLeft.y() + 10);
//   for(WorkingPackView * pack: workingPacks){
//       newTopLeft.setX(nr.x() + (wid + 5) * index);
//       pack->setGeometry(QRect(newTopLeft,QSize(wid, ((size.height() / 4) * 3 - 20))));
//       index++;
//   }



}

DeckView::~DeckView()
{
    delete ui;
    for(auto wp: workingPacks)
        delete wp;
    for(auto tp: targetPacks)
        delete tp;
    delete remainingPackView;
}
