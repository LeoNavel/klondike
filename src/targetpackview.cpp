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

void TargetPackView::paintEvent(QPaintEvent * e){
    QFrame::paintEvent(e);
//    if(!isEmpty()){
//        if(!currentCardView->isVisible())
//            currentCardView->show();
//    }
}

void TargetPackView::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);

    currentCardView->setGeometry(QRect(QPoint(0,0), QSize(r.width(),r.height())));
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

void TargetPackView::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)    // Left button...
  {
      if(!selectionDelegate->isEmpty()){
//            QPoint ep = mapToGlobal(selectionDelegate->pos());
//            ep.setX(ep.x() + 20);
//            ep.setY(ep.y() + 20);
//            QPoint p = mapToGlobal(pos());
//            if(ep.x() < p.x() || ep.y() < p.y() || ep.x() > p.x() + rect().width() || ep.y() > p.y() + rect().height())
//                return false;
          std::vector<card::Card> gs_p;
          gs_p = selectionDelegate->getAll();
          if(gs_p.size() > 1)
              selectionDelegate->rollBack();
          else {
              if(selectionDelegate->isWpv()){
                  WorkingPackView *wpv = static_cast<WorkingPackView *>(selectionDelegate->getSourcePack());
                  // todo
              } else {
                  RemainingPackView * rpv = static_cast<RemainingPackView *>(selectionDelegate->getSourcePack());
                  selectionDelegate->mainView->moveCards(rpv, this, 1);
              }


//              try {
//                  card::Card c = gs_p[0];
//                  push(c);
//                  currentCardView->set_number(c.get_number());
//                  currentCardView->set_sign(c.get_sign());
//              } catch (ErrorException err) {
//                  qDebug() << err.get_message().c_str();

//              }
          }

          QApplication::restoreOverrideCursor();
          selectionDelegate->clear();
          selectionDelegate->hide();
          update();

      }
  }


}


TargetPackView::~TargetPackView()
{
    delete ui;
}
