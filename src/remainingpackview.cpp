#include "remainingpackview.h"
#include "ui_remainingpackview.h"

RemainingPackView::RemainingPackView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RemainingPackView)
{
    ui->setupUi(this);
}

RemainingPackView::~RemainingPackView()
{
    delete ui;
}
