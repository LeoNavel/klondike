/*! 
 *  \file       TerminalCanvas.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "TerminalCanvas.hpp"

TerminalCanvas::TerminalCanvas() {
    height = CANVAS_HEIGHT;
    width = CANVAS_WIDTH;

    for (int y = 0; y < height; y ++ ){
        for (int x = 0 ; x < width; x++){
            canvas[y][x] = ' ';
        }
        canvas[y][width -1 ] = '\0';
    }

    canvas[0][CARD_WIDTH +2] = 'r';

    for (int i = 0 ; i < 4 ; i++) {
        canvas[0][29 + 4 + i*(CARD_WIDTH + 2)] = 't';
        canvas[0][29 + 4 + i*(CARD_WIDTH + 2) + 1] = 49 + i;
    }

    for (int i = 0 ; i < 7 ; i++){
        canvas[CARD_HEIGHT + 3][CARD_WIDTH/2 + i*(CARD_WIDTH + 1)] = 'w';
        canvas[CARD_HEIGHT + 3][CARD_WIDTH/2 + i*(CARD_WIDTH + 1) +1] = 49 + i;
    }
}

void TerminalCanvas::print() {
    clrscr();
    for (int y = 0  ; y < height ; y++) {
        std::cout << canvas[y] << std::endl;
    }
    std::cout << "\n\n";
}

void TerminalCanvas::make_card(int x, int y, card::Card *card) {

    //printing corners
    canvas[y][x] = '/';
    canvas[y][x+CARD_WIDTH-1] = '\\';
    canvas[y+CARD_HEIGHT-1][x] = '\\';
    canvas[y+CARD_HEIGHT-1][x+CARD_WIDTH-1] = '/';

    //creating lines
    for (int i = 0 ; i < CARD_WIDTH-2 ; i++){
        canvas[y][x+1+i] = '-';
        canvas[y+CARD_HEIGHT-1][x+1+i] = '_';
    }

    for (int i = 0 ; i < CARD_HEIGHT -2; i++){
        canvas[y+1+i][x] = '|';
        canvas[y+1+i][x+CARD_WIDTH-1] = '|';
    }


    char sign = make_sign(card->get_sign());
    char number = make_num(card->get_number());

    if (card->isTurnedUp()) {
        canvas[y + 1][x + 1] = sign;
        canvas[y + CARD_HEIGHT - 2][x + CARD_WIDTH - 2] = sign;

        if (number != '0'){
            canvas[y + CARD_HEIGHT - 2][x + 1] = number;
            canvas[y + CARD_HEIGHT - 2][x + 2] = ' ';
            canvas[y + 1][x + CARD_WIDTH - 2] = number;
            canvas[y + 1][x + CARD_WIDTH - 3] = ' ';
        }
        else {
            canvas[y + CARD_HEIGHT - 2][x + 1] = '1';
            canvas[y + CARD_HEIGHT - 2][x + 2] = number;
            canvas[y + 1][x + CARD_WIDTH - 3] = '1';
            canvas[y + 1][x + CARD_WIDTH - 2] = number;
        }
    }
}

void TerminalCanvas::make_card_title(int x, int y, card::Card *card) {
    canvas[y][x] = '/';
    canvas[y+1][x] = '|';
    canvas[y][x+CARD_WIDTH-1] = '\\';
    canvas[y+1][x+CARD_WIDTH-1] = '|';

    //creating lines
    for (int i = 0 ; i < CARD_WIDTH-2 ; i++){
        canvas[y][x+1+i] = '-';
        canvas[y+1][x+1+i] = ' ';
    }

    char sign = make_sign(card->get_sign());
    char number = make_num(card->get_number());

    if (card->isTurnedUp()){
        canvas[y + 1][x + 1] = sign;

        if (number != '0'){
            canvas[y + 1][x + CARD_WIDTH - 2] = number;
            canvas[y + 1][x + CARD_WIDTH - 3] = ' ';
        }
        else {
            canvas[y + 1][x + CARD_WIDTH - 3] = '1';
            canvas[y + 1][x + CARD_WIDTH - 2] = number;
        }
    }

}

void TerminalCanvas::clrscr() {
    #if defined(_WIN32) || defined(__MSDOS__)
    #include <conio.h>
    clrscr();
    #else
    system("clear");
    #endif

}

char TerminalCanvas::make_num(int num) {
    switch (num){
        case 1:
            return  'A';
        case 10:
            return '0';
        case 11:
            return 'J';
        case 12:
            return 'Q';
        case 13:
            return  'K';
        default:
            return static_cast<char>(num + 48);
    }
}

char TerminalCanvas::make_sign(enum card::sign sign) {
    switch (sign){
        case card::DIAMONDS:
            return CANVAS_DIAMOND;

        case card::SPADES:
            return CANVAS_SPADE;

        case card::CLUBS:
            return CANVAS_CLUB;

        case card::HEART:
            return CANVAS_HEART;
    }
    return 'X';
}

void TerminalCanvas::update(int id, card::Card *topTargetCard) {
    //calculating corner point
    int x, y;
    y = 1;
    x = 30 + (CARD_WIDTH + 2) * id;

    if (topTargetCard){
        make_card(x, y, topTargetCard);
    }
    else {
        delete_card(x,y);
    }

}

void TerminalCanvas::update(int id, CardStacks::GenericCardStack workingPack) {
    int x,y;
    y = CARD_HEIGHT + 5;
    x = 1 + id*(CARD_WIDTH + 1);

    long size = workingPack.size();

    delete_card(x,y);
    for (int i = 0 ; i < size - 1 ; i++){
        card::Card card = workingPack[i];
        make_card_title(x,y,&card);
        if (size > 10 and !card.get_visibility()) {
            y += 1;
        } else {
            y += 2;
        }
    }

    for (int i = y ; i < height - CARD_HEIGHT ; i+= CARD_HEIGHT){
        delete_card(x,i);
    }

    if (size > 0) {
        card::Card card = workingPack[size - 1];
        make_card(x, y, &card);
    }
}

void TerminalCanvas::update(CardStacks::RemainingPack *remainigPack) {
    int x = 1 , y = 1;
    card::Card card = card::Card();

    if (!remainigPack->allCardVisible()){
        make_card(x,y,&card);
    }
    else {
        delete_card(x,y);
    }

    if (remainigPack->isSetCurrent()){
        //card = ((*remainigPack)[remainigPack->get_current_id()]);
        card = remainigPack->currentCard();
        card.turnUp();
        make_card(x + 2 + CARD_WIDTH,y,&card);
    }
    else {
        delete_card(x + 2 + CARD_WIDTH,y);
    }
}

void TerminalCanvas::delete_card(int x, int y) {
    for (int j = 0; j < CARD_HEIGHT; j++) {
        for (int i = 0 ; i < CARD_WIDTH ; i++) {
            canvas[y+j][x+i] = ' ';
        }
    }
}
