#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include "myframe.h"
#include "deckview.h"
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    games.push_back(ui->framik);

    games[0]->setGeometry(this->rect());
    games[0]->prepareDeck(0 + 1);

//    ui->gridLayout->addWidget(all);
//    ui->gridLayout->addLayout(new DeckView, 0, 1);
//    ui->gridLayout->addLayout(new DeckView, 1, 0);
//    ui->gridLayout->addLayout(new DeckView, 1, 1);



//    MyFrame *frame = new MyFrame(this);
//    ui->verticalLayout->addWidget(frame);

//    setCentralWidget(ui->plainTextEdit);
    //disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

}

//void MainWindow::QResizeEvent(const QSize & size, const QSize & oldSize){
////    QMainWindow::QResizeEvent(size, oldSize);

//    qDebug() << "resizeee";
//}


void MainWindow::on_actionMore_games_triggered()
{
    qDebug() << "blah";
    QVBoxLayout *all = new QVBoxLayout;
    all->setAlignment(Qt::AlignCenter);

    QHBoxLayout *top = new QHBoxLayout;

//    top->setAlignment(Qt::AlignLeading);
    QString moreGames = "More games";
    QString oneGame = "One game";
    QAction * changeGamesNumberOption = ui->menuBar->actions()[0]->menu()->actions()[0];
    QString optionName = changeGamesNumberOption->text();
    if(optionName == moreGames) {
        changeGamesNumberOption->setText(oneGame);
        DeckView * ndv = new DeckView(this);
        ndv->prepareDeck(2);
        games.push_back(ndv);

        ndv = new DeckView(this);
        ndv->prepareDeck(3);
        games.push_back(ndv);

        ndv = new DeckView(this);
        ndv->prepareDeck(4);
        games.push_back(ndv);

        games[0]->setStyleSheet("background-color:#f00;");
        games[1]->setStyleSheet("background-color:#0f0;");
        games[2]->setStyleSheet("background-color:#00f;");
        games[3]->setStyleSheet("background-color:#0ff;");


        top->addWidget(games[0]);
        top->addWidget(games[1]);

        QHBoxLayout *bot = new QHBoxLayout;
        bot->addWidget(games[2]);
        bot->addWidget(games[3]);

        all->addLayout(top);
        all->addLayout(bot);

        ui->gridLayout->addLayout(all, 0, 0);
        games[0]->setGeometry(games[0]->rect());
        games[1]->setGeometry(games[0]->rect());
        games[2]->setGeometry(games[0]->rect());
        games[3]->setGeometry(games[0]->rect());

    } else {
        changeGamesNumberOption->setText(moreGames);
        qDebug() << "deleting";

        while(games.size() > 1) {
            DeckView * item = games.at(games.size() - 1);
            qDebug() << "bam";
            games.pop_back();
            delete item;
        }

        ui->gridLayout->addWidget(ui->framik);

        games[0]->setGeometry(this->rect());
    }
}

