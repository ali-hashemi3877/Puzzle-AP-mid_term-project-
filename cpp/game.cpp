#include "game.h"

void game::puzzle::show_puzzle(){
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< "\033[0m\033[32m" << puz[i][j] << " ";
        std::cout<< std::endl;
    }
    std::cout<< "\033[0m";
}

void game::puzzle::manhattan_distance(){
    for (int n{1}; n < 9; n++)
        for (int i{}; i < 3; i++)
            for (int j{}; j < 3; j++)
                if (n == puz[i][j]){
                    int row = abs(i - ((n-1) / 3));
                    int col = abs(j - ((n-1) % 3));
                    manhattan += row + col;
                }
}

void game::start(){
    std::cout<< "\n\n" << "\033[0m\033[33m*********************************** ";
    std::cout<< "\033[1m\033[31mSLIDING PUZZLE ! \033[0m\033[33m***********************************\n";
    std::cout<< "****************************************************************************************\033[0m\n";
    std::cout<< "\n\033[34mWelcome to this wonderful game! In this game we solve your 8 puzzle!\n";
    std::cout<< "OK! Now start the game!\nThe defult target of this game is:\n";
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< "\033[0m\033[32m" << target[i][j] << " ";
        std::cout<< std::endl;
    }
    std::cout<< "\033[0m\033[34mNow do you want from us to solve puzzle with respect to defult target or another target?\n";
    std::cout<< "(\033[0m\033[31mNote\033[0m\033[34m: if you choose another target you can't use A* algorithm)\n";
    std::cout<< "Please enter d or a.(defult target or another target)";
    std::cin >> defult_or_another;
    while (defult_or_another != 'a' && defult_or_another != 'd'){
        std::cout<< "ٌ\033[0m\033[31mWrong entry!\n\033[0m\033[34mPlease enter d or a.(defult target or another target)";
        std::cin >> defult_or_another;
    }
    if (defult_or_another == 'a'){
        std::cout<< "Please enter your target puzzle!\n";
        for (size_t i{}; i < 3; i++)
                for (size_t j{}; j < 3; j++)
                    std::cin >> target[i][j];
    }
    std::cout<< "Target is:\n";
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< "\033[0m\033[32m" <<target[i][j] << " ";
        std::cout<< std::endl;
    }
    std::cout<< "\033[0m\033[34m1: Do you want to solve a random puzzle?\n2: Do you want to solve your puzzle?\n";
    std::cout<< "Please enter 1 or 2.(random puzzle or your puzzle)";
    array puz{};
    int a{};
    std::cin >> a;
    while (a != 1 && a != 2){
        std::cout<< "ٌ\033[0m\033[31mWrong entry!\n\033[0m\033[34mPlease enter 1 or 2.(random puzzle or your puzzle)";
        std::cin >> a;
    }
    random_or_normal = a - 1;
    while (true){
        if (random_or_normal){
            std::cout<< "Pleas enter your puzzle.\n";
            for (size_t i{}; i < 3; i++)
                for (size_t j{}; j < 3; j++)
                    std::cin >> puz[i][j];
        }
        else{
            std::vector<int> ran{};
            srand(time(NULL));
            while (ran.size() < 9){
                int a = rand() % 9;
                bool f{true};
                for (size_t j{}; j < ran.size(); j++)
                    if (a == ran[j]){
                        f = false;
                        break;
                    }
                if (f)
                    ran.push_back(a);
            }
            for (size_t i{}; i < 3; i++)
                for (size_t j{}; j < 3; j++)
                    puz[i][j] = ran[3*i + j];
        }
        auto root = std::make_shared<puzzle>(puz);
        initial_puz = root;
        solvable();
        if (flag)
            break;
        else if(random_or_normal){
            std::cout<< "\033[0m\033[31mThis puzzle with respect to the target is unsolvable\n";
            std::cout<< "Please enter another puzzle!\n";
        }
    }
    std::cout<< "\033[0m\033[34mThis is initial puzzle:\n";
    initial_puz->show_puzzle();
    std::cout<< "\033[0m\033[34mNow you have to decide how to solve the puzzle. we have 3 method. choose one of them!\n";
    std::cout<< "1: DFS algorihtm. This algorithm take more time & more steps to solve the puzzle than other method\n";
    std::cout<< "(\033[0m\033[31mNote\033[0m\033[34m: In this method you have to choose the depth you want to search. Maybe we can't find the target in this depth & if you choose the depth greater than 250, there is possibility that we can't show all of the steps(Maximum steps we show is 250!)\n";
    std::cout<< "2: BFS algorithm. This algorithm is faster with fewer steps than DFS algorithm\n";
    if (defult_or_another == 'a'){
        std::cout<< "Please choose one of the methods.(1 for DFS, 2 for BFS)";
        std::cin >> search_algorithm;
        while (search_algorithm != 1 && search_algorithm != 2){
            std::cout<< "ٌ\033[0m\033[31mWrong entry!\n\033[0m\033[34mPlease choose one of the methods.(1 for DFS, 2 for BFS)";
            std::cin >> search_algorithm;
        }
    }
    else if(defult_or_another == 'd'){
        std::cout<< "3: A* algorithm. This algorithm is most efficient algorihtm we have!\n";
        std::cout<< "Please choose one of the methods.(1 for DFS, 2 for BFS & 3 for A*)";
        std::cin >> search_algorithm;
        while (search_algorithm != 1 && search_algorithm != 2 && search_algorithm != 3){
            std::cout<< "ٌ\033[0m\033[31mWrong entry!\n\033[0m\033[34mPlease choose one of the methods.(1 for DFS, 2 for BFS & 3 for A*)";
            std::cin >> search_algorithm;
        }
    }
}

void game::solvable(){
    array puz{initial_puz->puz};
    std::array<int, 9> arr{};
    std::array<int, 9> dest{};
    int invertion_d{};
    int invertion_a{};
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++){
            arr[3*i + j] = puz[i][j];
            dest[3*i + j] = target[i][j];
        }
    for (size_t i{}; i < 8; i++)
        for (size_t j{i+1}; j < 9; j++){
            if ((arr[i]&&arr[j]) && arr[i] > arr[j])
                invertion_a++;
            if ((dest[i]&&dest[j]) && dest[i] > dest[j])
                invertion_d++;
        }
    if (invertion_a % 2 == invertion_d % 2){
        not_checked.push_back(initial_puz);
        all_puz.push_back(initial_puz);
        flag = true;
    }
    else
        flag = false;
}

std::vector<std::shared_ptr<game::puzzle>> game::set_children(std::shared_ptr<puzzle> puz){
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
        bool f{true};
        for (size_t j{}; j < all_puz.size(); j++)
            if (all_puz[j]->puz == arr)
                f = false;
        if (f){
            auto ptr = std::make_shared<puzzle>(arr);
            ptr->parent = puz;
            not_checked.push_back(ptr);
            all_puz.push_back(ptr);
            puz->children.push_back(ptr);
            ptr->no_move = puz->no_move + 1;
            if (search_algorithm == 3){
                ptr->manhattan_distance();
                ptr->periority = ptr->manhattan + ptr->no_move;
            }
        }
    }
    return puz->children;
}

void game::BFS_search(){
    int i{};
    while(flag && i < 362880){
        if (check(not_checked[0]->puz)){
            std::cout<< "\033[0m\033[1m\033[33mwe find the answer\n";
            break;
        }
        set_children(not_checked[0]);
        checked.push_back(not_checked[0]);
        not_checked.erase(not_checked.begin());
        i++;
    }
}

void game::DFS_search(){
    int depth{};
    std::cout<< "Please enter the depth you want.";
    std::cin >> depth;
    int i{};
    bool f{true};
    children = not_checked;
    if (check(not_checked[0]->puz)){
        std::cout<< "\033[0m\033[1m\033[33mwe find the answer\n";
        f = false;
    }
    if (f){
        children = set_children(not_checked[0]);
        while(i < 362880){
            if (check(children[0]->puz)){
                std::cout<< "\033[0m\033[1m\033[33mwe find the answer\n";
                break;
            }
            checked.push_back(children[0]);
            while (children.size() > 1 && set_children(children[0]).size() == 0){
                children[0]->parent->children.erase(children[0]->parent->children.begin());
                children.erase(children.begin());
            }
            if (set_children(children[0]).size() == 0){
                children[0]->parent->children.erase(children[0]->parent->children.begin());
                std::shared_ptr<puzzle> p{};
                if (children[0]->parent->parent != nullptr)
                    p = children[0]->parent->parent;
                else{
                    std::cout<< "\033[1m\033[31mSorry! We can't find the answer in this depth!\033[0m\n";
                    flag = false;
                    break;
                }
                while (p->children.size() == 0 && flag){
                    if (p->parent != nullptr)
                        p = p->parent;
                    else
                        flag = false;
                }
                if (flag)
                    children = p->children;
                else{
                    std::cout<< "\033[1m\033[31mSorry! We can't find the answer in this depth!\033[0m\n";
                    flag = false;
                    break;
                }
            }
            else{
                children[0]->parent->children.erase(children[0]->parent->children.begin());
                if (children[0]->no_move == depth){
                    if (children.size() > 1)
                        children.erase(children.begin());
                    else{
                        std::shared_ptr<puzzle> p{};
                        if (children[0]->parent->parent != nullptr)
                            p = children[0]->parent->parent;
                        else{
                            std::cout<< "\033[1m\033[31mSorry! We can't find the answer in this depth!\033[0m\n";
                            flag = false;
                            break;
                        }
                        while (p->children.size() == 0 && flag){
                            if (p->parent != nullptr)
                                p = p->parent;
                            else
                                flag = false;
                        }
                        if (flag){
                            children = p->children;
                        }
                        else{
                            std::cout<< "\033[1m\033[31mSorry! We can't find the answer in this depth!\033[0m\n";
                            flag = false;
                            break;
                        }
                    }
                }
                else
                    children = set_children(children[0]);
            }
            i++;
        }
    }
}

void game::A_star_search(){
    int i{};
    while(flag && i < 362880){
        if (check(not_checked[0]->puz)){
            std::cout<< "\033[0m\033[1m\033[33mwe find the answer\n";
            break;
        }
        set_children(not_checked[0]);
        checked.push_back(not_checked[0]);
        not_checked.erase(not_checked.begin());
        auto cost {[](std::shared_ptr<puzzle> p1, std::shared_ptr<puzzle> p2){ return p1->periority < p2->periority; }};
        std::sort(not_checked.begin(), not_checked.end(), cost);
        i++;
    }
}

void game::show_steps(){
    if (flag){
        std::shared_ptr<puzzle> puz{nullptr};
        if (search_algorithm == 1)
            puz = children[0];
        else if (search_algorithm == 2 || search_algorithm == 3)
            puz = not_checked[0];
        int i{};
        while (puz != nullptr){
            steps.push_front(puz);
            puz = puz->parent;
            i++;
        }
        for (size_t i{}; i < steps.size(); i++){
            std::cout<< "\033[0m\033[34mstep " << i+1 << ":\n";
            steps[i]->show_puzzle();
        }
    }
}