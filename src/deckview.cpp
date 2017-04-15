#include "deckview.h"
#include "ui_deckview.h"
#include "cardview.h"
#include <QDebug>

DeckView::DeckView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DeckView)
{
    ui->setupUi(this);

    CardStacks::CardDeck cardDeck = CardStacks::CardDeck();

    cardDeck.shuffleCards();

    CardStacks::GenericCardStack gs = CardStacks::GenericCardStack();
    CardStacks::GenericCardStack gs1 = CardStacks::GenericCardStack();

    while(!cardDeck.isEmpty())
        gs.push(cardDeck.topAndPop());
    while(!gs.isEmpty())
        gs1.push(gs.topAndPop());
    ui->remainingCards->initWithStack(gs1);

    CardView *cv1 = new CardView(this);
    cv1->setGeometry(QRect(0, 100, 200, 150));

    CardView *cv2 = new CardView(5, card::sign::HEART, this);
    cv2->setGeometry(QRect(160, 100, 200, 150));
    cv2->turnUp();

    CardView *cv3 = new CardView(10, card::sign::SPADES, this);
    cv3->setGeometry(QRect(160 * 2, 100, 200, 150));

    CardView *cv4 = new CardView(12, card::sign::DIAMONDS, this);
    cv4->setGeometry(QRect(160 * 3, 100, 200, 150));

    CardView *cv5 = new CardView(1, card::sign::CLUBS, this);
    cv5->setGeometry(QRect(160 * 4, 100, 200, 150));

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
