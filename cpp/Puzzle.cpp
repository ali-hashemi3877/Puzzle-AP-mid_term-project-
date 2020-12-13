#include "Puzzle.h"


void puzzle::get_puzzle(){
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++)
            std::cin >> puz[i][j];
    auto ptr_puzz = std::make_shared<puzzle>(puz);
    all_puz.push_back(ptr_puzz);
}

void puzzle::show_puzzle(){
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< puz[i][j] << " ";
        std::cout<< std::endl;
    }
}

std::vector<std::shared_ptr<puzzle>> puzzle::get_children(){
    int index[2] = {};
    int sign[2] = {-1, 1};
    std::vector<std::array<int,2>> zero_index{};
    for (size_t i{}; i < 3; i++){                 // find zero coordinate
        for (size_t j{}; j < 3; j++){
            if (puz[i][j] == 0){
                index[0] = i;
                index[1] = j;
            }
        }
    }
    for (int i{}; i < 2; i++){     // find zeros coordinates of next states
        for (int j{}; j < 2; j++){
            if (index[i]+sign[j] >= 0 && index[i]+sign[j] < 3){
                if (i == 0){
                    std::array<int,2> z = {index[i]+sign[j], index[i+1]};
                    zero_index.push_back(z);
                }
                else{
                    std::array<int,2> z = {index[i-1], index[i]+sign[j]};
                    zero_index.push_back(z);
                }
            }
        }
    }
    for (size_t i{}; i < zero_index.size(); i++){     // create next states
        std::array<std::array<int, 3>, 3> arr = puz;
        arr[index[0]][index[1]] = arr[zero_index[i][0]][zero_index[i][1]];
        arr[zero_index[i][0]][zero_index[i][1]] = 0;
        if (this->parent != nullptr){
            if (this->parent->puz == arr){
                auto ptr_arr = std::make_shared<puzzle>(arr);
                all_puz.push_back(ptr_arr);
                children.push_back(ptr_arr);
                children[children.size() - 1]->parent = std::make_shared<puzzle>(puz);
            }
        }
        else{
            auto ptr_arr = std::make_shared<puzzle>(arr);
            all_puz.push_back(ptr_arr);
            children.push_back(ptr_arr);
            children[children.size() - 1]->parent = std::make_shared<puzzle>(puz);
        }
    }
    return children;
}