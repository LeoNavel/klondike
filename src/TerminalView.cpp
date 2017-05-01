#include "TerminalView.hpp"

void TerminalView::refresh() {
    canvas.print();
}

int TerminalView::run() {
    std::cout<<"allooo" << std::endl;
    return 0;
}

void TerminalView::update(int id, card::Card *topTargetCard) {
    canvas.update(id, topTargetCard);
    refresh();
}

void TerminalView::update(int id, CardStacks::GenericCardStack workingPack) {
    canvas.update(id, workingPack);
    refresh();
}

void TerminalView::update(CardStacks::RemainingPack *remainigPack) {
    canvas.update(remainigPack);
    refresh();
}

void TerminalView::highlightNextCardCommand() {
    GenericView::highlightNextCardCommand();
}

void TerminalView::highlightRemainingToWorking(unsigned int id) {
    GenericView::highlightRemainingToWorking(id);
}

void TerminalView::highlightRemainingToTarget(unsigned int id) {
    GenericView::highlightRemainingToTarget(id);
}
