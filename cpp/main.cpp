#include <iostream>
#include <array>
#include "Puzzle.h"

int main(){
    puzzle puz{};
    array arr = puz.get_puzzle();
    puz.search();
    // std::vector<array> children = puz.get_children();
    // std::vector<array> not_order = puz.get_not_order();
    std::vector<std::shared_ptr<puzzle>> all_puzzle = puz.get_all_puzzle();
    for (size_t i{}; i < all_puzzle.size(); i++){
        std::cout<< "children " << i+1 << ":\n";
        puz.show_puzzle(all_puzzle[i]->get_puz());
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
    // int t{};
    // while(true){
    //     int count{};
    //     std::cout<< "floor " << t+1 << ": ";
    //     for (size_t i{}; i < floor.size(); i++){
    //         for (size_t j{}; j < floor[i].size(); j++){
    //             std::cout<< "state " << count+1 << ":\n";
    //             count++;
    //             floor[i][j]->show_puzzle();
    //             if (puz.check(floor[i][j])){
    //                 std::cout<< "this is the answer:\n";
    //                 floor[i][j]->show_puzzle();
    //                 break;
    //             }
    //         }
    //     }
    //     std::vector<std::vector<std::shared_ptr<puzzle>>> next_floor{};
    //     for (size_t i{}; i < floor.size(); i++)
    //         for (size_t j{}; j < floor[i].size(); j++)
    //             next_floor.push_back(floor[i][j]->get_children());
    //     floor = next_floor;
    //     t++;
    // }
    // for (size_t i{}; i < 3; i++){
    //     for (size_t j{}; j < 3; j++)
    //         std::cout<< arr[i][j] << " ";
    //     std::cout<< std::endl;
    // }
    return 0;
}