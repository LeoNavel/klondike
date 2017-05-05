/*! 
 *  \file       TerminalCanvas.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef TERMINAL_CANVAS_H
#define TERMINAL_CANVAS_H

#include "CardStacks.hpp"
#include "Card.hpp"

#define CANVAS_WIDTH 90
#define CANVAS_HEIGHT 45
#define CARD_WIDTH 8
#define CARD_HEIGHT 6

#if defined(_WIN32) || defined(__MSDOS__)
    #define CANVAS_SPADE   "\x06"
    #define CANVAS_CLUB    "\x05"
    #define CANVAS_HEART   "\x03"
    #define CANVAS_DIAMOND "\x04"
#else
    #define CANVAS_SPADE   'S'
    #define CANVAS_CLUB    'C'
    #define CANVAS_HEART   'H'
    #define CANVAS_DIAMOND 'D'
#endif

class TerminalCanvas {
private:
    int width;
    int height;
    char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

public:
    /**
     * Init all char of canvas to space.
     */
    TerminalCanvas();

    /**
     * Clear terminal.
     */
    void clrscr();

    /**
     * Print canvas to stdout.
     */
    void print();

    /**
     * Create card in position x,y.
     * @param x
     * @param y
     */
    void make_card(int x, int y, card::Card *card);

    /**
     * Insert spaces into rectangle from x,y to x+width,y+height
     * @param x
     * @param y
     */
    void delete_card(int x, int y);

    /**
     * Make only first lines of card. -> borders + sign, number
     * @param x
     * @param y
     * @param card
     */
    void make_card_title(int x, int y, card::Card *card);

    /**
     * Make char from number.
     * @param num
     * @return
     */
    char make_num(int num);

    /**
     * Make char sign form sign of card.
     * @return
     */
    char make_sign(enum card::sign);

    /**
     * Update Target pack with topTargetCard.
     * @param id which target pack is updated
     * @param topTargetCard
     */
    void update(int id, card::Card * topTargetCard);

    /**
     * Update working pack
     * @param id whic working pack is updated
     * @param workingPack
     */
    void update(int id, CardStacks::GenericCardStack workingPack);

    /**
     * Update workipack view.
     * @param remainigPack ptr to remaining pack from deck.
     */
    void update(CardStacks::RemainingPack *remainigPack);
};

#endif //TERMINAL_CANVAS_H