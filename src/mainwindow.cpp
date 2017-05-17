/*! 
 *  \file       mainwindow.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deckview.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->hide();
    Deck *theDeck = new Deck();
    theDeck->prepareDeck(1);
    DeckView *theView = new DeckView(this);
    QRect r = this->rect();
    r.setY(50);
    theView->setGeometry(r);
    Controller *theController = new Controller(theDeck, theView);

    views.push_back(theView);
    controllers.push_back(theController);


    disableRemoveGame();
    for(int i = 1; i < 4; i++){
        disableUndo(i);
        disableSave(i);
        disableLoad(i);
        disableHelp(i);
        disableNewGame(i);
    }
    enableNewGame(1);
}

void MainWindow::disableUndo(unsigned int i){
    QAction * editAction = ui->menuBar->actions()[1];
    QAction * undo = editAction->menu()->actions()[0];
    QAction * undoItem = undo->menu()->actions()[i];
    undoItem->setEnabled(false);
}

void MainWindow::enableUndo(unsigned int i){
    QAction * editAction = ui->menuBar->actions()[1];
    QAction * undo = editAction->menu()->actions()[0];
    QAction * undoItem = undo->menu()->actions()[i];
    undoItem->setEnabled(true);
}

void MainWindow::enableSave(unsigned int i){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * save = fileAction->menu()->actions()[2];
    QAction * saveItem = save->menu()->actions()[i];
    saveItem->setEnabled(true);
}

void MainWindow::disableSave(unsigned int i){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * save = fileAction->menu()->actions()[2];
    QAction * saveItem = save->menu()->actions()[i];
    saveItem->setEnabled(false);
}

void MainWindow::disableLoad(unsigned int i){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * load = fileAction->menu()->actions()[3];
    QAction * loadItem = load->menu()->actions()[i];
    loadItem->setEnabled(false);
}

void MainWindow::enableLoad(unsigned int i){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * load = fileAction->menu()->actions()[3];
    QAction * loadItem = load->menu()->actions()[i];
    loadItem->setEnabled(true);
}

void MainWindow::disableHelp(unsigned int i){
    QAction * helpAction = ui->menuBar->actions()[2];
    QAction * help = helpAction->menu()->actions()[0];
    QAction * helpItem = help->menu()->actions()[i];
    helpItem->setEnabled(false);
}

void MainWindow::enableHelp(unsigned int i){
    QAction * helpAction = ui->menuBar->actions()[2];
    QAction * help = helpAction->menu()->actions()[0];
    QAction * helpItem = help->menu()->actions()[i];
    helpItem->setEnabled(true);
}

MainWindow::~MainWindow()
{
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
//        dv->resizeEvent(event);

        QRect r = this->rect();
        r.setY(30);
        dv->setGeometry(r);
    } else {
        int h = (ns.height() - 30) / 2;
        int w = ns.width() / 2;
        for(unsigned int i = 0; i < controllers.size(); i++){
            DeckView * dv = views[i];
            dv->resize(w, h);
            if(i == 1 || i == 3){
                dv->move(w,dv->pos().y());
            }
            if(i == 2 || i == 3){
                dv->move(dv->pos().x(), h + 30);
            }
        }
    }
}

void MainWindow::enableNewGame(unsigned int i){

    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * new_game = fileAction->menu()->actions()[0];
    QAction * newGameItem = new_game->menu()->actions()[i];
    newGameItem->setEnabled(true);
}

void MainWindow::disableNewGame(unsigned int i){
    QAction * fileAction = ui->menuBar->actions()[0];
    QAction * new_game = fileAction->menu()->actions()[0];
    QAction * newGameItem = new_game->menu()->actions()[i];
    newGameItem->setEnabled(false);
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


void MainWindow::newGame(unsigned int i){
    if(controllers.size() == i) {
        enableRemoveGame();
        unsigned int size = controllers.size();
        enableUndo(size);
        enableSave(size);
        enableLoad(size);
        enableHelp(size);
        if(size < 3)
            enableNewGame(size + 1);
        QRect r = this->rect();
        r.setY(30);
        r.setWidth(r.width() / 2);
        r.setHeight(r.height() / 2);

        if(size == 1){
            views[0]->setGeometry(r);

            Deck * newDeck = new Deck();
            newDeck->prepareDeck(3);
            DeckView *newView = new DeckView(this);
            r.moveTo(r.width(), 30);
            newView->setGeometry(r);
            newView->show();

            Controller *newController = new Controller(newDeck, newView);
            views.push_back(newView);
            controllers.push_back(newController);
        }else if(size == 2){
            Deck * newDeck = new Deck();
            newDeck->prepareDeck(3);
            DeckView *newView = new DeckView(this);
            r.moveTo(0, r.height() + 30);
            newView->setGeometry(r);
            newView->show();

            Controller *newController = new Controller(newDeck, newView);
            views.push_back(newView);
            controllers.push_back(newController);
        } else if(size == 3){
            Deck * newDeck = new Deck();
            newDeck->prepareDeck(3);
            DeckView *newView = new DeckView(this);
            r.moveTo(r.width(), r.height() + 30);
            newView->setGeometry(r);
            newView->show();

            Controller *newController = new Controller(newDeck, newView);
            views.push_back(newView);
            controllers.push_back(newController);
        }
    } else {
        Controller * controller = controllers[i];
        controller->restartGame();
    }
}

void MainWindow::on_actionRemove_game_triggered()
{
    unsigned int size = controllers.size();
    if(size > 1){
        DeckView * dv = views[views.size() - 1];
//        delete dv;
        views.pop_back();

        Controller * controller = controllers[size - 1];
        delete controller;
        controllers.pop_back();
        disableUndo(size - 1);
        disableSave(size - 1);
        disableLoad(size - 1);
        disableHelp(size - 1);
        if(size < 4)
            disableNewGame(size);
    }
    if(size == 2){
        DeckView *dv = views[0];
        QRect r = this->rect();
        r.setY(30);
        dv->setGeometry(r);
    }
    if(size == 2){
        disableRemoveGame();
    }
}

void MainWindow::on_actionFirst_game_triggered()
{
    Controller *controller = controllers[0];
    controller->undo_command();
}

void MainWindow::on_actionSecond_game_triggered()
{
    Controller *controller = controllers[1];
    controller->undo_command();
}

void MainWindow::on_actionThird_game_triggered()
{
    Controller *controller = controllers[2];
    controller->undo_command();
}

void MainWindow::on_actionFourth_game_triggered()
{
    Controller *controller = controllers[3];
    controller->undo_command();
}

void MainWindow::save(unsigned int i){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save game"), "",
            tr("game (*.klondike)"), 0, QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty())
        return;
    Controller *controller = controllers[i];
    std::string fn = fileName.toStdString();

    controller->save(fn);
}

void MainWindow::on_actionSave_first_game_triggered()
{
    save(0);
}

void MainWindow::on_actionSave_second_game_triggered()
{
    save(1);
}

void MainWindow::on_actionSave_third_game_triggered()
{
    save(2);
}

void MainWindow::on_actionSave_fourth_game_triggered()
{
    save(3);
}

void MainWindow::load(unsigned int i){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open klondike game"), "",
            tr("klondike (*.klondike);;All Files (*)"), 0, QFileDialog::DontUseNativeDialog);
    if(fileName.isEmpty())
        return;
    std::string fn = fileName.toStdString();
    Controller * controller = controllers[i];
    controller->load(fn);
}

void MainWindow::on_actionLoad_to_first_game_triggered()
{
    load(0);
}

void MainWindow::on_actionLoad_to_second_game_triggered()
{
    load(1);
}

void MainWindow::on_actionLoad_to_third_game_triggered()
{
    load(2);
}

void MainWindow::on_actionLoad_to_fourth_game_triggered()
{
    load(3);
}

void MainWindow::findHelp(unsigned int i){
    Controller * controller = controllers[i];
    controller->findHelp();
}

void MainWindow::on_actionHelp_for_first_game_triggered()
{
    findHelp(0);
}

void MainWindow::on_actionHelp_for_second_game_triggered()
{
    findHelp(1);
}



void MainWindow::on_actionHelp_for_third_game_triggered()
{
    findHelp(2);
}

void MainWindow::on_actionHelp_for_fourth_game_triggered()
{
    findHelp(3);
}

void MainWindow::on_actionFirst_game_2_triggered()
{
    newGame(0);
}

void MainWindow::on_actionSecond_game_2_triggered()
{
    newGame(1);
}

void MainWindow::on_actionThird_game_2_triggered()
{
    newGame(2);
}

void MainWindow::on_actionFourth_game_2_triggered()
{
    newGame(3);
}
