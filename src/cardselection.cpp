/*! 
 *  \file       cardselection.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
/**************************************
 *   Project :               Solitaire
 *   Authors :               xklemb00, xtomas32
 *   Created :               25.03.2017
 *   Compiled:               g++ 6.3.1
 *
 *   Notes :         Card selection definition
 *
 ***************************************/

#include "cardselection.h"
#include "ui_cardselection.h"
#include "workingpackview.h"
#include "remainingpackview.h"

CardSelection::CardSelection(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CardSelection)
{
    ui->setupUi(this);
    setObjectName("CardSelection");
    setStyleSheet("#CardSelection{background-color: rgba(1,1,1,0); border:none}");
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
        c->raise();
    }
}
void CardSelection::setMainView(DeckView * mainView){
    this->mainView = mainView;
}

unsigned int CardSelection::getSize(){
    return cards.size();
}


void CardSelection::setGeometry(const QRect &r) {
    QFrame::setGeometry(r);
    update();
}

bool CardSelection::isWpv(){
    return this->wpv;
}

void * CardSelection::getSourcePack(){
    return sourcePack;
}

bool CardSelection::isEmpty(){
    return cards.size() == 0;
}
void CardSelection::push(card::Card c) {
    CardView * ncv = new CardView(c.get_number(), c.get_sign(), this);
    ncv->turnUp();
    cards.push_back(ncv);
    this->setMouseTracking(true);
    for(CardView * c:cards)
        c->setMouseTracking(true);
}

void CardSelection::push(CardStacks::GenericCardStack stack){
    clear();
    while(!stack.isEmpty())
        push(stack.topAndPop());

    this->setMouseTracking(true);
    for(CardView * c:cards)
        c->setMouseTracking(true);
//    this->setAttribute(Qt::WA_Hover);
//    cards[cards.size()-1]->setAttribute(Qt::WA_Hover);
}

void CardSelection::clear() {
    for(auto c:cards)
        delete c;
    cards.clear();
}

std::vector<card::Card> CardSelection::getAll(){
    std::vector<card::Card> vc = std::vector<card::Card>();
    for(int i = cards.size()-1; i > -1; i--){
        CardView * c = cards[i];
        vc.push_back(card::Card(c->get_number(), c->get_sign()));
    }
//    clear();
//    hide();
    return vc;
}

void CardSelection::setWpv(bool wpv){
    this->wpv = wpv;
}

void CardSelection::rollBack() {
    if(wpv){
        WorkingPackView * wpv = static_cast<WorkingPackView *>(sourcePack);
        if(!wpv->anyVisible()){
            CardView * fc = cards[cards.size()-1];
            cards.pop_back();
            wpv->push_invisible(card::Card(fc->get_number(), fc->get_sign()));
            wpv->turn_invisible();
        }
        for(int i = cards.size()-1; i > -1; i--){
            wpv->push(card::Card(cards[i]->get_number(), cards[i]->get_sign(), true));
        }
        wpv->update();
    } else {
        RemainingPackView * rpv = static_cast<RemainingPackView *>(sourcePack);
        CardView * vw = cards[0];
        rpv->insertCurrent(card::Card(vw->get_number(), vw->get_sign(), true));
        rpv->update();
    }

    clear();
    hide();
}

void CardSelection::setSourcePack(void *wpv){
    sourcePack = wpv;
}

void CardSelection::setOffset(QPoint p){
    offset = p;
}

QPoint CardSelection::getOffset() {
    return offset;
}

CardSelection::~CardSelection()
{
    delete ui;
}
