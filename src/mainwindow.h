/*! 
 *  \file       mainwindow.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
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
    void resizeEvent(QResizeEvent* event);
    ~MainWindow();

private slots:
    /**
     * remove game action
     */
    void on_actionRemove_game_triggered();

    /**
     * undo first game
     */
    void on_actionFirst_game_triggered();

    /**
     * undo second game
     */
    void on_actionSecond_game_triggered();

    /**
     * undo third game
     */
    void on_actionThird_game_triggered();

    /**
     * undo fourth game
     */
    void on_actionFourth_game_triggered();

    /**
     * save first game
     */
    void on_actionSave_first_game_triggered();

    /**
     * save first game
     */
    void on_actionSave_second_game_triggered();

    /**
     * save first game
     */
    void on_actionSave_third_game_triggered();

    /**
     * save first game
     */
    void on_actionSave_fourth_game_triggered();

    /**
     * load first game
     */
    void on_actionLoad_to_first_game_triggered();

    /**
     * load second game
     */
    void on_actionLoad_to_second_game_triggered();

    /**
     * load third game
     */
    void on_actionLoad_to_third_game_triggered();

    /**
     * load fourth game
     */
    void on_actionLoad_to_fourth_game_triggered();

    /**
     * get help for first game
     */
    void on_actionHelp_for_first_game_triggered();

    /**
     * get help for second game
     */
    void on_actionHelp_for_second_game_triggered();

    /**
     * get help for third game
     */
    void on_actionHelp_for_third_game_triggered();

    /**
     * get help for fourth game
     */
    void on_actionHelp_for_fourth_game_triggered();

    /**
     * new first game
     */
    void on_actionFirst_game_2_triggered();

    /**
     * new second game
     */
    void on_actionSecond_game_2_triggered();

    /**
     * new third game
     */
    void on_actionThird_game_2_triggered();

    /**
     * new fourth game
     */
    void on_actionFourth_game_2_triggered();

private:
    /**
     * enable new game option
     * @param i number of game
     */
    void enableNewGame(unsigned int i);

    /**
     * disable new game option
     * @param i number of game
     */
    void disableNewGame(unsigned int i);

    /**
     * enable remove game option
     */
    void enableRemoveGame();

    /**
     * disable remove game option
     */
    void disableRemoveGame();

    /**
     * disable undo option
     *
     * @param i number of option
     */
    void disableUndo(unsigned int i);

    /**
     * enable undo option
     *
     * @param i number of option
     */
    void enableUndo(unsigned int i);

    /**
     * enable save option
     *
     * @param i number of option
     */
    void enableSave(unsigned int i);

    /**
     * disable save option
     *
     * @param i number of option
     */
    void disableSave(unsigned int i);

    /**
     * enable load option
     *
     * @param i number of option
     */
    void enableLoad(unsigned int i);

    /**
     * disable load option
     *
     * @param i number of option
     */
    void disableLoad(unsigned int i);

    /**
     * enable help option
     *
     * @param i number of option
     */
    void enableHelp(unsigned int);

    /**
     * disable help option
     *
     * @param i number of option
     */
    void disableHelp(unsigned int);

    /**
     * save game
     *
     * @param i number of game
     */
    void save(unsigned int i);

    /**
     * load game
     *
     * @param i number of game
     */
    void load(unsigned int i);

    /**
     * find help for game
     *
     * @param i number of game
     */
    void findHelp(unsigned int i);

    /**
     * create new game
     *
     * @param i number of game
     */
    void newGame(unsigned int i);

    Ui::MainWindow *ui;
    std::vector<DeckView *> views;
    std::vector<Controller *> controllers;

};

#endif // MAINWINDOW_H
