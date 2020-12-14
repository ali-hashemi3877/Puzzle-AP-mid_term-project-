#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <array>
#include <vector>
#include <memory>

using array = std::array<std::array<int, 3>, 3>;

class puzzle{
    private:
        array puz{};
        array target = {1,2,3,4,5,6,7,8,0};
        std::vector<array> children;
        std::vector<array> not_order;
    public:
        puzzle(array puzzle) : puz{puzzle} {}
        puzzle() = default;
        array get_puzzle();
        void show_puzzle(array puz);
        std::vector<array>get_children(array puz);
        bool check(array puz) { return puz == target; }
        std::vector<array> search();

};
#endif