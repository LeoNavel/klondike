#include "View.hpp"


void GenericView::update(CardStacks::RemainingPack *remainigPack){
    qDebug() << "omg..";
}

void GenericView::update(CardStacks::TargetPack *targetPack){

}

void GenericView::update(CardStacks::WorkingPack *workingPack){

}

void GenericView::setController(Controller *controller){
    this->controller = controller;
}

GenericView::~GenericView(){

}
