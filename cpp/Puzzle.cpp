#include "Puzzle.h"


array puzzle::get_puzzle(){
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++)
            std::cin >> puz[i][j];
    children.push_back(puz);
    return puz;
}

void puzzle::show_puzzle(array puz){
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< puz[i][j] << " ";
        std::cout<< std::endl;
    }
}

std::vector<array> puzzle::get_children(array puz){
    int index[2] = {};
    int move[2] = {-1, 1};
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
            if (index[i]+move[j] >= 0 && index[i]+move[j] < 3){
                if (i == 0){
                    std::array<int,2> z = {index[i]+move[j], index[i+1]};
                    zero_index.push_back(z);
                }
                else{
                    std::array<int,2> z = {index[i-1], index[i]+move[j]};
                    zero_index.push_back(z);
                }
            }
        }
    }
    for (size_t i{}; i < zero_index.size(); i++){     // create next states
        array arr = puz;
        arr[index[0]][index[1]] = arr[zero_index[i][0]][zero_index[i][1]];
        arr[zero_index[i][0]][zero_index[i][1]] = 0;
        bool flag{true};
        for (size_t j{}; j < not_order.size(); j++)
            if (not_order[j] == arr)
                flag = false;
        if (flag)
            children.push_back(arr);
    }
    return children;
}

std::vector<array> puzzle::search(){
    int i{};
    std::vector<array> child{};
    while(i < 2){
        if (check(children[0]))
            return children;
        show_puzzle(children[0]);
        child = get_children(children[0]);
        not_order.push_back(children[0]);
        show_puzzle(not_order[0]);
        children.erase(children.begin());
        show_puzzle(children[0]);
        i++;
    }
    return child;
}