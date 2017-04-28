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
    virtual void update(CardStacks::WorkingPack * workingPack);
    virtual void update(CardStacks::RemainingPack *remainigPack);
};

#endif //VIEW_H
