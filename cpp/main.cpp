#include <iostream>
#include <array>
#include "Puzzle.h"

int main(){
    puzzle puz{};
    puz.get_puzzle();
    while(true){
        std::vector<std::shared_ptr<puzzle>> children = puz.get_children();
        for (size_t i{}; i < children.size(); i++){
            std::cout<< "state " << i+1 << ":\n";
            children[i]->show_puzzle();
            if (puz.check(children[i])){
                std::cout<< "this is the answer:\n";
                children[i]->show_puzzle();
            }
        }
        break;
    }
    // for (size_t i{}; i < 3; i++){
    //     for (size_t j{}; j < 3; j++)
    //         std::cout<< arr[i][j] << " ";
    //     std::cout<< std::endl;
    // }
    return 0;
}