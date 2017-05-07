/*! 
 *  \file       targetpackview.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "targetpackview.h"
#include "ui_targetpackview.h"
#include "deckview.h"

TargetPackView::TargetPackView(QWidget *parent) :
    QFrame(parent),
     CardStacks::TargetPack(),
    ui(new Ui::TargetPackView)
{
    ui->setupUi(this);
    this->currentCardView = new CardView(this);
    this->currentCardView->turnUp();
    currentCardView->hide();
}

void TargetPackView::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);

    currentCardView->setGeometry(QRect(QPoint(0,0), QSize(r.width(),r.height())));
//    r.setWidth(currentCardView->rect().width());
//    r.setHeight(currentCardView->rect().height());
    QRect nr = QRect(r.x(), r.y(), currentCardView->rect().width(), currentCardView->rect().height());
    QFrame::setGeometry(nr);
}

void TargetPackView::setTopCard(card::Card *card){
    if(card == nullptr){
        currentCardView->hide();
    } else {
        if(!currentCardView->isVisible()){
            currentCardView->show();
        }
        currentCardView->set_number(card->get_number());
        currentCardView->set_sign(card->get_sign());
    }
}

card::sign TargetPackView::getColor() {
    return currentCardView->get_sign();
}

void TargetPackView::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)    // Left button...
  {
      if(!selectionDelegate->isEmpty()){
          std::vector<card::Card> gs_p;
          gs_p = selectionDelegate->getAll();
              if(selectionDelegate->isWpv()){
                  WorkingPackView *wpv = static_cast<WorkingPackView *>(selectionDelegate->getSourcePack());
                  selectionDelegate->mainView->moveCardsToTargetPack(wpv, this, selectionDelegate->getSize());
              } else {
                  selectionDelegate->mainView->moveCardsFromRemainingPack(this);
              }
          selectionDelegate->clear();
          selectionDelegate->hide();
          selectionDelegate->mainView->updateCursor();
          update();

      }
  }


}

void TargetPackView::highlight(){
    if(currentCardView->isVisible()){
        QString ss = currentCardView->styleSheet();
        currentCardView->setStyleSheet("background-color: #d00;");
        QTime dieTime= QTime::currentTime().addMSecs(250);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        currentCardView->setStyleSheet(ss);
        update();
    } else {
        QFrame * fram = new QFrame(this);
        fram->setGeometry(currentCardView->rect());
        fram->setStyleSheet("background-color: #d00;");
        fram->show();
        QTime dieTime= QTime::currentTime().addMSecs(250);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        delete fram;
    }
}

TargetPackView::~TargetPackView()
{
    delete ui;
}
