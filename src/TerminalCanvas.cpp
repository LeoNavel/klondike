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
}

void TerminalCanvas::print() {
    clrscr();
    for (int y = 0  ; y < height ; y++) {
        std::wcout << canvas[y] << std::endl;
    }
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
}

void TerminalCanvas::update(int id, card::Card *topTargetCard) {
    //calculating corner point
    int x,y;
    y = 1;
    x =  30 +  (CARD_WIDTH + 2)*id;

    make_card(x,y, topTargetCard);

}

void TerminalCanvas::make_card(int x, int y, card::Card *card) {

    //printing corners
    canvas[y][x] = '/';
    canvas[y][x+CARD_WIDTH-1] = '\\';
    canvas[y+CARD_WIDTH-1][x] = '\\';
    canvas[y+CARD_WIDTH-1][x+CARD_WIDTH-1] = '/';

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
        canvas[y + CARD_HEIGHT - 2][x + 1] = number;
        canvas[y + 1][x + CARD_WIDTH - 2] = number;
        canvas[y + CARD_HEIGHT - 2][x + CARD_WIDTH - 2] = sign;
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
    }

    if (card->isTurnedUp()){
        canvas[y+1][x+1] = make_sign(card->get_sign());
        canvas[y+1][x+CARD_WIDTH-1] = make_num(card->get_number());
    }

}

void TerminalCanvas::clrscr() {
    for (int i = 0 ; i < 10 ; i++) {
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    }
}

void TerminalCanvas::update(int id, CardStacks::GenericCardStack workingPack) {
    int x,y;
    y = CARD_HEIGHT + 3;
    x = 1 + id*(CARD_WIDTH + 1);

    long size = workingPack.size();

    for (int i = 0 ; i < size - 1 ; i++){
        card::Card card = workingPack[i];
        make_card_title(x,y,&card);
    }


    card::Card card = workingPack[size -1];
    make_card(x,y,&card);
}

char TerminalCanvas::make_num(int num) {
    switch (num){
        case 1:
            return  'A';
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

void TerminalCanvas::update(CardStacks::RemainingPack *remainigPack) {
    int x = 1 , y = 1;
    card::Card card = card::Card();

    if (!remainigPack->allCardVisible()){
        make_card(x,y,&card);
    }

    if (remainigPack->isSetCurrent()){
        card = ((*remainigPack)[remainigPack->get_current_id()]);
        make_card(x,y,&card);
    }
}
