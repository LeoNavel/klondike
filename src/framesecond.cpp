#include "framesecond.h"
#include "ui_framesecond.h"
#include <QMouseEvent>

FrameSecond::FrameSecond(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameSecond)
{
    ui->setupUi(this);
}

FrameSecond::~FrameSecond()
{
    delete ui;
}

void FrameSecond::mousePressEvent(QMouseEvent *event) {
    qDebug() << "asda";
//    qDebug() << event->pos();
    offset = event->pos();
}

void FrameSecond::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
}
