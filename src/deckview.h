#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QFrame>
#include <QResizeEvent>

namespace Ui {
class DeckView;
}

class DeckView : public QFrame
{
    Q_OBJECT

public:
    explicit DeckView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    ~DeckView();

private:
    Ui::DeckView *ui;
};

#endif // DECKVIEW_H
