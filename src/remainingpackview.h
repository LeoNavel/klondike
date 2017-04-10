#ifndef REMAININGPACKVIEW_H
#define REMAININGPACKVIEW_H

#include <QFrame>

namespace Ui {
class RemainingPackView;
}

class RemainingPackView : public QFrame
{
    Q_OBJECT

public:
    explicit RemainingPackView(QWidget *parent = 0);
    ~RemainingPackView();

private:
    Ui::RemainingPackView *ui;
};

#endif // REMAININGPACKVIEW_H
