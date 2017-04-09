#include "cardview.h"
#include "ui_cardview.h"
#include <QDebug>

CardView::CardView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CardView)
{
    ui->setupUi(this);

}

void CardView::setGeometry(const QRect &r) {
    int newHeight = (defaultSize.height * r.width()) / defaultSize.width;
    int newWidth = (defaultSize.width * r.height()) / defaultSize.height;
    QRect nr;
    if (newWidth > r.width())
        nr = QRect(r.x(), r.y(), r.width(), newHeight);
    else
        nr = QRect(r.x(), r.y(), newWidth, r.height());

    QFrame::setGeometry(nr);

    int paddingTB = nr.width() * 0.05;
    int paddingLR = nr.width() * 0.05 + 3;

    QRect l1 = ui->numberTopLeft->rect();

    l1.setX(paddingLR);
    l1.setY(paddingTB);
    l1.setWidth(20);
    l1.setHeight(20);
    ui->numberTopLeft->setGeometry(l1);


    QRect l2 = ui->numberBottomRight->rect();
    l2.setX(nr.width() - paddingLR - l2.width());
    l2.setY(nr.height() - paddingTB - l2.height());
    l2.setWidth(20);
    l2.setHeight(20);
    ui->numberBottomRight->setGeometry(l2);

    QRect l3 = ui->imageLabel->rect();
    l3.setX((nr.width() - 50) /2);
    l3.setY((nr.height() - 54) / 2);
    l3.setWidth(50);
    l3.setHeight(54);
    ui->imageLabel->setGeometry(l3);
}

CardView::~CardView()
{
    delete ui;
}
