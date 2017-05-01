#ifndef TERMINAL_CANVAS_H
#define TERMINAL_CANVAS_H

#include "CardStacks.hpp"
#include "Card.hpp"

#define CANVAS_WIDTH 70
#define CANVAS_HEIGHT 20
#define CARD_WIDTH 8
#define CARD_HEIGHT 8

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
    wchar_t canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

public:
    /**
     * Init all char of canvas to space.
     */
    TerminalCanvas();

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

    void make_card_title(int x, int y, card::Card *card);

    char make_num(int num);

    char make_sign(enum card::sign);

    void update(int id, card::Card * topTargetCard);
    void update(int id, CardStacks::GenericCardStack workingPack);
    void update(CardStacks::RemainingPack *remainigPack);
};

#endif //TERMINAL_CANVAS_H