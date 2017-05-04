/*! 
 *  \file       cardview.h
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QFrame>
#include "Card.hpp"
#include <QMouseEvent>


namespace Ui {
class CardView;
}

class CardView : public QFrame, public card::Card
{
    Q_OBJECT
public:
    struct {
        int width = 125;
        int height = 175;
    } defaultSize;
    /**
     * construct view for card
     *
     * @param parent parenting widget
     *
     * @return CardView
     */
    explicit CardView(QWidget *parent = 0);

    /**
     * construct view for card
     *
     * @param value card value
     * @param sign card sign
     * @param parent parenting widget
     * @return CardView
     */
    CardView(int value, card::sign sign, QWidget *parent = 0);

    /**
     * set geometry
     *
     * @param r rectangle
     */
    void setGeometry(const QRect &r);

    /**
     * redraw card
     */
    void redrawCard();

    /**
     * turn card up
     */
    void turnUp();

    /**
     * set card sign
     *
     * @param card_sign card sign
     */
    void set_sign(card::sign card_sign);

    /**
     * set card number
     *
     * @param number number
     */
    void set_number(int number);

    ~CardView();

private:
    Ui::CardView *ui;
    QPoint offset;

};

#endif // CARDVIEW_H
