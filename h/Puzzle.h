#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <array>
#include <vector>
#include <memory>

class puzzle{
    private:
        std::array<std::array<int, 3>, 3> puz{};
        std::shared_ptr<puzzle> parent;
        std::vector<std::shared_ptr<puzzle>> children;
        std::vector<std::shared_ptr<puzzle>> all_puz;
    public:
        puzzle(std::array<std::array<int, 3>, 3> puzzle) : puz{puzzle} {}
        puzzle() = default;
        void get_puzzle();
        void show_puzzle();
        std::vector<std::shared_ptr<puzzle>>get_children();
};
#endif