#include "myframe.h"
#include "ui_myframe.h"
#include <QMouseEvent>
#include <QDebug>

MyFrame::MyFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MyFrame)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MyFrame::~MyFrame()
{
    delete ui;
}

void MyFrame::mouseReleaseEvent(QMouseEvent * event) {
    qDebug() << "tata";
}

void MyFrame::dropEvent(QDropEvent *event)
{
    qDebug() << "tuto";
//    textBrowser->setPlainText(event->mimeData()->text());
//    mimeTypeCombo->clear();
//    mimeTypeCombo->addItems(event->mimeData()->formats());

//    event->acceptProposedAction();
}
