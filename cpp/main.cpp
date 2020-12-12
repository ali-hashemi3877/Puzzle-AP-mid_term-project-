#include <iostream>
#include <array>
#include "Puzzle.h"

int main(){
    puzzle puz{};
    puz.get_puzzle();
    std::vector<std::shared_ptr<puzzle>> p = puz.get_children();
    for (int i{}; i < p.size(); i++)
        p[i]->show_puzzle();
    return 0;
}