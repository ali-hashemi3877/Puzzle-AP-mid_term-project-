#include <iostream>
#include <array>
#include <deque>
#include <stdlib.h>
#include "game.h"

int main(){
    game game{};
    game.get_puzzle();
    if (game.search_algorithm == 1)
        game.DFS_search();
    else if (game.search_algorithm == 2)
        game.BFS_search();
    else
        game.A_star_search();
    game.show_steps();
    return 0;
}