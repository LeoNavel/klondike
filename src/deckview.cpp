#include "deckview.h"
#include "ui_deckview.h"
#include "cardview.h"
#include <QDebug>

DeckView::DeckView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DeckView)
{
    ui->setupUi(this);

    this->cardSelection = new CardSelection(this);
    cardSelection->hide();

    CardStacks::CardDeck cardDeck = CardStacks::CardDeck();

    cardDeck.shuffleCards();


    for(int i = 0; i < 7; i++){
        WorkingPackView * nwpv = new WorkingPackView(this);
        nwpv->selectionDelegate = cardSelection;
        workingPacks.push_back(nwpv);
        for(int j = 0; j < i; j++)
            workingPacks[i]->push_invisible(cardDeck.topAndPop());

        workingPacks[i]->push_invisible(cardDeck.topAndPop());
        workingPacks[i]->turn_invisible();
    }


    ui->remainingCards->initWithStack(cardDeck);
    ui->remainingCards->selectionDelegate = cardSelection;


//    CardView *cv1 = new CardView(this);
//    cv1->setGeometry(QRect(0, 100, 200, 150));

//    CardView *cv2 = new CardView(5, card::sign::HEART, this);
//    cv2->setGeometry(QRect(160, 100, 200, 150));
//    cv2->turnUp();

//    CardView *cv3 = new CardView(10, card::sign::SPADES, this);
//    cv3->setGeometry(QRect(160 * 2, 100, 200, 150));

//    CardView *cv4 = new CardView(12, card::sign::DIAMONDS, this);
//    cv4->setGeometry(QRect(160 * 3, 100, 200, 150));

//    CardView *cv5 = new CardView(1, card::sign::CLUBS, this);
//    cv5->setGeometry(QRect(160 * 4, 100, 200, 150));

//    setCentralWidget()
}

void DeckView::resizeEvent(QResizeEvent* event)
{
   QFrame::resizeEvent(event);
   QSize size = event->size();
   QRect ar = ui->remainingCards->rect();
   ar.setTopLeft(QPoint(5, 5));
   QRect nr = QRect(ar.topLeft(), QSize((size.width() / 7) * 2 + 10, size.height() / 4));
   ui->remainingCards->setGeometry(nr);

   int index = 0;
   int wid = (size.width() / 7) - 5;
   QPoint newTopLeft = nr.bottomLeft();
   newTopLeft.setY(newTopLeft.y() + 10);
   for(WorkingPackView * pack: workingPacks){
       newTopLeft.setX(nr.x() + (wid + 5) * index);
       pack->setGeometry(QRect(newTopLeft,QSize(wid, ((size.height() / 4) * 3 - 20))));
       index++;
//       pack->setGeometry(QRect(newTopLeft,QSize((size.width() / 7) - 5, (size.height() / 4))));

   }

}


void DeckView::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)    // Left button...
  {
    // Do something related to the left button
      qDebug() << "a";
  }
  else if (e->button() == Qt::RightButton)   // Right button...
  {
    // Do something related to the right button
      qDebug() << "a";
  }
  else if (e->button() == Qt::MidButton)   // Middle button...
  {
    // Do something related to the middle button
      qDebug() << "a";
  }
}

DeckView::~DeckView()
{
    delete ui;
}
