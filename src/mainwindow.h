

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
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
//    void QResizeEvent(const QSize & size, const QSize & oldSize);
    void resizeEvent(QResizeEvent* event);
    ~MainWindow();

protected:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);



private slots:

    void on_actionMore_games_triggered();

private:
    Ui::MainWindow *ui;
    myDialog *mDialog;
    std::vector<DeckView *> games;

};

#endif // MAINWINDOW_H
