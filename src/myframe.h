#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>

namespace Ui {
class MyFrame;
}

class MyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MyFrame(QWidget *parent = 0);
    ~MyFrame();
    void dropEvent(QDropEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Ui::MyFrame *ui;
};

#endif // MYFRAME_H
