#ifndef VIEW_H
#define VIEW_H

#include "CardStacks.hpp"
#include "QDebug"

class Controller; // TODO try to compile

class GenericView {
protected:
    Controller * controller = nullptr;
public:
    void setController(Controller *controller);
    ~GenericView();

    virtual void update(int id, card::Card * topTargetCard);
    virtual void update(int id, CardStacks::GenericCardStack workingPack);
    virtual void update(CardStacks::RemainingPack *remainigPack);
    virtual void highlightNextCardCommand();
    virtual void highlightRemainingToWorking(unsigned int id);
    virtual void highlightRemainingToTarget(unsigned int id);
};

#endif //VIEW_H
