#include "View.hpp"


void GenericView::update(CardStacks::RemainingPack *remainigPack){
}

void GenericView::update(int id, card::Card * topTargetCard){

}

void GenericView::update(int id, CardStacks::GenericCardStack workingPack){

}

void GenericView::highlightNextCardCommand(){

}

void GenericView::highlightRemainingToWorking(unsigned int id){

}

void GenericView::highlightRemainingToTarget(unsigned int id){

}

void GenericView::setController(Controller *controller){
    this->controller = controller;
}

void GenericView::highlightWorkingToTarget(unsigned int workingDeckID, unsigned int targetDeckID){

}

void GenericView::highlightWorkingToWorking(unsigned int sourceID, unsigned int count, unsigned int destinationID){

}

void GenericView::finishGame(){

}

GenericView::~GenericView(){

}
