#include <iostream>
#include <array>
#include <deque>
#include "Puzzle.h"

int main(){
    puzzle puz{};
    array arr = puz.get_puzzle();
    puz.search();
    std::deque<std::shared_ptr<puzzle>> steps = puz.find_steps();
    // std::vector<array> children = puz.get_children();
    // std::vector<array> not_order = puz.get_not_order();
    std::vector<std::shared_ptr<puzzle>> all_puzzle = puz.get_all_puzzle();
    for (size_t i{}; i < steps.size(); i++){
        std::cout<< "step " << i+1 << ":\n";
        puz.show_puzzle(steps[i]->get_puz());
    }
    // for (size_t i{}; i < not_order.size(); i++){
    //     std::cout<< "not_order " << i+1 << ":\n";
    //     puz.show_puzzle(not_order[i]);
    // }
    // std::vector<array> v = puz.set_children(arr);
    // for (size_t i{}; i < v.size(); i++){
    //     std::cout<< "state " << i+1 << ":\n";
    //     puz.show_puzzle(v[i]);
    // }
    // std::vector<std::vector<array>> floor{};
    // floor.push_back(puz.search());
    // for (size_t i{}; i < floor.size(); i++){
    //     for (size_t j{}; j < floor[i].size(); j++){
    //         std::cout<< "state " << j+1 << ":\n";
    //         puz.show_puzzle(floor[i][j]);
    //     }
    // }
    return 0;
}