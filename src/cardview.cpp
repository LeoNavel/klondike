/*! 
 *  \file       cardview.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "cardview.h"
#include "ui_cardview.h"
#include "remainingpackview.h"

CardView::CardView(QWidget *parent) :
    QFrame(parent),
    card::Card(1, card::sign::CLUBS),
    ui(new Ui::CardView)
{
    ui->setupUi(this);
    redrawCard();

}

CardView::CardView(int value, card::sign sign, QWidget *parent): CardView(parent){
    Card::set_number(value);
    Card::set_sign(sign);
    redrawCard();
}

void CardView::set_number(int number) {
    Card::set_number(number);
    redrawCard();
}

void CardView::set_sign(card::sign card_sign) {
    Card::set_sign(card_sign);
    redrawCard();
}

void CardView::redrawCard() {
    ui->back->hide();
    if(Card::isTurnedUp()){
        int value = Card::get_number();
        card::sign sign = Card::get_sign();
        QString valueS;
        switch(value) {
        case 1:
            valueS = "A";
            break;
        case 11:
            valueS = "J";
            break;
        case 12:
            valueS = "Q";
            break;
        case 13:
            valueS = "K";
            break;
        default:
            valueS.setNum(value);
        }

        ui->numberBottomRight->setText(valueS);
        ui->numberTopLeft->setText(valueS);
        QString imgSrc;
        switch (sign) {
        case card::sign::DIAMONDS:
            imgSrc = "piko";
            break;
        case card::sign::SPADES:
            imgSrc = "list";
            break;
        case card::sign::HEART:
            imgSrc = "srdce";
            break;
        default:
            imgSrc = "zalud";
        }

        QString img = "background-image: url(\":/icons/resources/" + imgSrc + ".png\")";
        QString imgMini = "background-image: url(\":/icons_15/resources/" + imgSrc + "@15.png\")";
        ui->imageLabel->setStyleSheet(img);
        ui->iconBottom->setStyleSheet(imgMini);
        ui->iconTop->setStyleSheet(imgMini);
    } else {
        ui->back->show();
    }
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
    l1.setWidth(40);
    l1.setHeight(20);
    ui->numberTopLeft->setGeometry(l1);

    QRect l2 = ui->numberBottomRight->rect();
    l2.setX(nr.width() - paddingLR - 40);
    l2.setY(nr.height() - paddingTB - 20);
    l2.setWidth(40);
    l2.setHeight(20);
    ui->numberBottomRight->setGeometry(l2);

    QRect l3 = ui->iconTop->rect();
    l3.setX(nr.width() - paddingLR - 15);
    l3.setY(paddingTB);
    l3.setWidth(14);
    l3.setHeight(15);
    ui->iconTop->setGeometry(l3);

    QRect l4 = ui->iconBottom->rect();
    l4.setX(paddingLR);
    l4.setY(nr.height() - paddingTB - 14);
    l4.setWidth(14);
    l4.setHeight(15);
    ui->iconBottom->setGeometry(l4);

    QRect l5 = ui->imageLabel->rect();
    l5.setX((nr.width() - 50) /2);
    l5.setY((nr.height() - 54) / 2);
    l5.setWidth(50);
    l5.setHeight(54);
    ui->imageLabel->setGeometry(l5);

    ui->back->setGeometry(QRect(QPoint(0,0), nr.size()));
}

void CardView::turnUp() {
    Card::turnUp();
    redrawCard();
}


CardView::~CardView()
{
    delete ui;
}
