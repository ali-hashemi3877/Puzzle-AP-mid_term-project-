#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <memory>

using array = std::array<std::array<int, 3>, 3>;

class puzzle{
    private:
        array puz{};
        array target = {1,4,2,6,3,5,7,0,8};
        std::vector<array> children;
        std::vector<array> not_order;
        std::shared_ptr<puzzle> parent;
        std::vector<std::shared_ptr<puzzle>> all_puzzle;
        std::deque<std::shared_ptr<puzzle>> steps;
    public:
        puzzle(array puzzle) : puz{puzzle} {}
        puzzle() = default;
        array get_puzzle();
        void show_puzzle(array puz);
        std::vector<array> set_children(array puz);
        bool check(array puz) { return puz == target; }
        void search();
        std::shared_ptr<puzzle> find_puzzle(array target);
        std::deque<std::shared_ptr<puzzle>> find_steps();
        std::vector<array> get_children() { return children; }
        std::vector<array> get_not_order() { return not_order; }
        std::vector<std::shared_ptr<puzzle>> get_all_puzzle() { return all_puzzle; }
        array get_puz() { return puz; }      
};
#endif