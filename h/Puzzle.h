#ifndef PUZZLE_H
#define PUZZLE_H

#include <array>

std::array<std::array<int, 3>, 3> get_puzzle();
void show_puzzle(std::array<std::array<int, 3>, 3> arr);

#endif