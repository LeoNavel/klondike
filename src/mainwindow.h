

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mydialog.h"
#include "deckview.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);



private slots:
    void on_actionNew_Window_triggered();

    void on_actionAnother_game_triggered();

private:
    Ui::MainWindow *ui;
    myDialog *mDialog;
    std::vector<DeckView *> games;

};

#endif // MAINWINDOW_H
