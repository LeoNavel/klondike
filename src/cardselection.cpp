#include "cardselection.h"
#include "ui_cardselection.h"
#include "workingpackview.h"

CardSelection::CardSelection(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CardSelection)
{
    ui->setupUi(this);
}

void CardSelection::paintEvent(QPaintEvent *e){
    QFrame::paintEvent(e);

    QRect nr = this->rect();
    nr.setY(0);
    for(int i = cards.size()-1; i > -1; i--) {
        CardView *c = cards[i];
        if((unsigned) i == cards.size()-1)
            nr.setTopLeft(QPoint(0, 0));
        else {
            if(cards.size() > 17)
                nr.setTopLeft(QPoint(0, 19 + nr.y()));
            else if (cards.size() > 10)
                nr.setTopLeft(QPoint(0, 20 + nr.y()));
            else
                nr.setTopLeft(QPoint(0, 25 + nr.y()));
        }
        nr.setSize(this->rect().size());
        c->setGeometry(nr);
        c->show();
    }
}

void CardSelection::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);
    update();
}


bool CardSelection::isEmpty(){
    return cards.size() == 0;
}
void CardSelection::push(card::Card c) {
    CardView * ncv = new CardView(c.get_number(), c.get_sign(), this);
    ncv->turnUp();
    cards.push_back(ncv);
}

void CardSelection::push(CardStacks::GenericCardStack stack){
    clear();
    while(!stack.isEmpty())
        push(stack.topAndPop());

    this->setMouseTracking(true);
    cards[cards.size()-1]->setMouseTracking(true);
//    this->setAttribute(Qt::WA_Hover);
//    cards[cards.size()-1]->setAttribute(Qt::WA_Hover);
}

void CardSelection::clear() {
    for(auto c:cards)
        delete c;
    cards.clear();
}

CardStacks::GenericCardStack CardSelection::getAll(){
    CardStacks::GenericCardStack gs = CardStacks::GenericCardStack();
    for(int i = cards.size()-1; i > -1; i--){
        CardView * c = cards[i];
        gs.push(card::Card(c->get_number(), c->get_sign()));
    }
//    clear();
//    hide();
    return gs;
}

void CardSelection::rollBack() {
    WorkingPackView * wpv = static_cast<WorkingPackView *>(sourcePack);
    CardView * fc = cards[cards.size()-1];
    cards.pop_back();
    wpv->push_invisible(card::Card(fc->get_number(), fc->get_sign()));
    wpv->turn_invisible();
    for(int i = cards.size()-1; i > -1; i--){
        wpv->push(card::Card(cards[i]->get_number(), cards[i]->get_sign(), true));
    }
    clear();
    hide();
}

//void CardSelection::mousePressEvent(QMouseEvent * event){
//    if()
//}

void CardSelection::setSourcePack(void *wpv){
    sourcePack = wpv;
}

void CardSelection::mouseMoveEvent(QMouseEvent *event){
    if(!isEmpty()){
        QPoint np = mapToParent(event->pos() - offset);
        if(np.y() < 0 || np.x() < 0){
            qDebug() << "nope na hraniciach";
        } else
            this->move(np);
    }
}

void CardSelection::setOffset(QPoint p){
    offset = p;
}

CardSelection::~CardSelection()
{
    delete ui;
}
