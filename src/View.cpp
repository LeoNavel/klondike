#include "View.hpp"


void GenericView::update(CardStacks::RemainingPack *remainigPack){
    qDebug() << "omg..";
}

void GenericView::update(int id, card::Card * topTargetCard){

}

void GenericView::update(int id, CardStacks::GenericCardStack workingPack){

}

void GenericView::setController(Controller *controller){
    this->controller = controller;
}

GenericView::~GenericView(){

}