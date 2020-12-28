#include <iostream>
#include <array>
#include <deque>
#include "game.h"

int main(){
    game game{};
    game.get_puzzle();
    // game.solvable();
    // game.set_children(game.get_arr());
    // for (size_t i{}; i < game.not_checked.size(); i++){
    //     std::cout<< "child " << i+1 << ":\n";
    //     game.not_checked[i]->show_puzzle();
    // }
    game.DFS_search();
    //game.show_steps();
    return 0;
}