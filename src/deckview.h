#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QFrame>

namespace Ui {
class DeckView;
}

class DeckView : public QFrame
{
    Q_OBJECT

public:
    explicit DeckView(QWidget *parent = 0);
    ~DeckView();

private:
    Ui::DeckView *ui;
};

#endif // DECKVIEW_H
