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

//        cardSelection->installEventFilter(workingPacks[i]);
    }


    ui->remainingCards->initWithStack(cardDeck);
    ui->remainingCards->selectionDelegate = cardSelection;

    for(int i = 0; i < 4; i++) {
        TargetPackView * tpv = new TargetPackView(this);
        tpv->selectionDelegate = cardSelection;
        targetPacks.push_back(tpv);
//        cardSelection->installEventFilter(targetPacks[i]);
    }
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
