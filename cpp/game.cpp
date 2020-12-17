#include "game.h"

void game::puzzle::show_puzzle(){
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< puz[i][j] << " ";
        std::cout<< std::endl;
    }
}

void game::get_puzzle(){
    array puz{};
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++)
            std::cin >> puz[i][j];
    auto root = std::make_shared<puzzle>(puz);
    initial_puz = root;    
}

bool game::solvable(){
    array puz{initial_puz->puz};
    std::array<int, 9> arr{};
    int invertion{};
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++)
            arr[3*i + j] = puz[i][j];
    for (size_t i{}; i < 8; i++)
        for (size_t j{i+1}; j < 9; j++)
            if ((arr[i]&&arr[j]) && arr[i] > arr[j])
                invertion++;
    if (invertion % 2 == 0){
        not_checked.push_back(initial_puz);
        return true;
    }
    else{
        std::cout<< "This puzzle is unsolvable\n";
        return false;
    }
}

void game::set_children(std::shared_ptr<puzzle> puz){
    int index[2] = {};
    int move[2] = {-1, 1};
    std::vector<std::array<int,2>> zero_index{};
    array arr_puz{puz->puz};
    for (size_t i{}; i < 3; i++){                 // find zero coordinate
        for (size_t j{}; j < 3; j++){
            if (arr_puz[i][j] == 0){
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
        array arr = arr_puz;
        arr[index[0]][index[1]] = arr[zero_index[i][0]][zero_index[i][1]];
        arr[zero_index[i][0]][zero_index[i][1]] = 0;
        bool flag{true};
        //for (size_t j{}; j < not_checked.size(); j++)
        if (puz->parent != nullptr)
            if (puz->parent->puz == arr)
                flag = false;
        if (flag){
            auto ptr = std::make_shared<puzzle>(arr);
            ptr->parent = puz;
            not_checked.push_back(ptr);
        }
    }
}

void game::BFS_search(){
    bool flag{solvable()};
    int i{};
    while(flag && i < 1000){
        if (check(not_checked[0]->puz)){
            std::cout<< "we find the answer\n";
            not_checked[0]->show_puzzle();
            break;
        }
        set_children(not_checked[0]);
        checked.push_back(not_checked[0]);
        not_checked.erase(not_checked.begin());
        i++;
    }
}

void game::show_steps(){
    std::shared_ptr<puzzle> puz = not_checked[0];
    int i{};
    while (puz != nullptr){
        steps.push_front(puz);
        puz = puz->parent;
        i++;
    }
    for (size_t i{}; i < steps.size(); i++){
        std::cout<< "step " << i+1 << ":\n";
        steps[i]->show_puzzle();
    }
}