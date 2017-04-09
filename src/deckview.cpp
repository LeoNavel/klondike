#include "deckview.h"
#include "ui_deckview.h"

DeckView::DeckView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DeckView)
{
    ui->setupUi(this);
}

DeckView::~DeckView()
{
    delete ui;
}
