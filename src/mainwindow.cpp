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
    statusBar()->hide();
//    games.push_back(ui->framik);
    Deck *theDeck = new Deck();
    theDeck->prepareDeck(1);
    DeckView *theView = new DeckView(this);
    theView->setGeometry(this->rect());
    Controller *theController = new Controller(theDeck, theView);

    views.push_back(theView);
    controllers.push_back(theController);


    disableRemoveGame();
}

MainWindow::~MainWindow()
{
    for(DeckView * v: views)
        delete v;
    for(Controller *c: controllers)
        delete c;
    delete ui;

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   const QSize ns = event->size();

    if(controllers.size() == 1) {
        DeckView *dv = views[0];
        dv->resizeEvent(event);
    } else {
        int h = ns.height() / 2;
        int w = ns.width() / 2;
        for(unsigned int i = 0; i < controllers.size(); i++){
            DeckView * dv = views[i];
            dv->resize(w, h);
            if(i == 1 || i == 3){
                dv->move(w,dv->pos().y());
            }
            if(i == 2 || i == 3){
                dv->move(dv->pos().x(), h);
            }
        }
    }
}

void MainWindow::enableNewGame(){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * addGame = fileAction->menu()->actions()[0];
    addGame->setEnabled(true);
}

void MainWindow::disableNewGame(){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * addGame = fileAction->menu()->actions()[0];
    addGame->setEnabled(false);
}

void MainWindow::enableRemoveGame(){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * removeGame = fileAction->menu()->actions()[1];
    removeGame->setEnabled(true);
}

void MainWindow::disableRemoveGame(){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * removeGame = fileAction->menu()->actions()[1];
    removeGame->setEnabled(false);
}


void MainWindow::on_actionMore_games_triggered()
{
    if(controllers.size() < 4){
        enableRemoveGame();
        unsigned int size = controllers.size();
        QRect r = this->rect();
        r.setWidth(r.width() / 2);
        r.setHeight(r.height() / 2);

        if(size == 1){
            views[0]->setGeometry(r);

            Deck * newDeck = new Deck();
            newDeck->prepareDeck(3);
            DeckView *newView = new DeckView(this);
            r.moveTo(r.width(), 0);
            newView->setGeometry(r);
            newView->show();

            Controller *newController = new Controller(newDeck, newView);
            views.push_back(newView);
            controllers.push_back(newController);
        }else if(size == 2){
            Deck * newDeck = new Deck();
            newDeck->prepareDeck(3);
            DeckView *newView = new DeckView(this);
            r.moveTo(0, r.height());
            newView->setGeometry(r);
            newView->show();

            Controller *newController = new Controller(newDeck, newView);
            views.push_back(newView);
            controllers.push_back(newController);
        } else if(size == 3){
        Deck * newDeck = new Deck();
        newDeck->prepareDeck(3);
        DeckView *newView = new DeckView(this);
        r.moveTo(r.width(), r.height());
        newView->setGeometry(r);
        newView->show();

        Controller *newController = new Controller(newDeck, newView);
        views.push_back(newView);
        controllers.push_back(newController);
        }
    }
    if(controllers.size() == 4){
        disableNewGame();
    }
}


void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "cmd z";
    Controller * controller = controllers[0];
    controller->undo_command();
}

void MainWindow::on_actionRemove_game_triggered()
{
    if(controllers.size() > 1){
        enableNewGame();
        DeckView * dv = views[views.size() - 1];
        delete dv;
        views.pop_back();

        Controller * controller = controllers[controllers.size() - 1];
        delete controller;
        controllers.pop_back();
    }
    if(controllers.size() == 1){
        DeckView * dv = views[0];
        dv->setGeometry(rect());
    }
    if(controllers.size() == 1){
        disableRemoveGame();
    }
}
