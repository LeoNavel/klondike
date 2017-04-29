

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "mydialog.h"
#include "deckview.h"
#include "Controller.hpp"
#include "QFileDialog"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//    void QResizeEvent(const QSize & size, const QSize & oldSize);
    void resizeEvent(QResizeEvent* event);
    ~MainWindow();

protected:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);



private slots:

    void on_actionMore_games_triggered();

//    void on_actionUndo_triggered();

    void on_actionRemove_game_triggered();

    void on_actionFirst_game_triggered();

    void on_actionSecond_game_triggered();

    void on_actionThird_game_triggered();

    void on_actionFourth_game_triggered();

    void on_actionSave_first_game_triggered();

private:
    void enableNewGame();
    void disableNewGame();
    void enableRemoveGame();
    void disableRemoveGame();
    void disableUndo(unsigned int i);
    void enableUndo(unsigned int i);

    Ui::MainWindow *ui;
    myDialog *mDialog;
    std::vector<DeckView *> views;
    std::vector<Controller *> controllers;

};

#endif // MAINWINDOW_H
