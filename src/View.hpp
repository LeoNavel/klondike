#ifndef VIEW_H
#define VIEW_H


class Controller; // TODO try to compile

class GenericView {
public:
    GenericView(Controller *controller);
    ~GenericView();

    void update();
};

#endif //VIEW_H