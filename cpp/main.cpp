#include <iostream>
#include <array>
#include "Puzzle.h"

int main(){
    std::array<std::array<int, 3>, 3> arr{get_puzzle()};
    show_puzzle(arr);
    return 0;
}