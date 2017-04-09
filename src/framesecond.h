#ifndef FRAMESECOND_H
#define FRAMESECOND_H

#include <QFrame>
#include <QDebug>

namespace Ui {
class FrameSecond;
}

class FrameSecond : public QFrame
{
    Q_OBJECT

public:
    explicit FrameSecond(QWidget *parent = 0);
    ~FrameSecond();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::FrameSecond *ui;
    QPoint offset;
};

#endif // FRAMESECOND_H
