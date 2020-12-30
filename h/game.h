#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <memory>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using array = std::array<std::array<int, 3>, 3>;

class game{
    public:
        class puzzle{
            public:
                array puz{};
                std::shared_ptr<puzzle> parent;
                std::vector<std::shared_ptr<puzzle>> children{};
                int no_move{};
                int manhattan{};
                int periority{};
                puzzle(array puzzle) : puz{puzzle} {}
                puzzle() = default;
                void show_puzzle();
                void manhattan_distance();
        };
        std::shared_ptr<puzzle> initial_puz{};
        array target = {1,2,3,4,5,6,7,8,0};
        bool flag{true};
        int random_or_normal{};
        int search_algorithm{};
        char defult_or_another{};
        std::vector<std::shared_ptr<puzzle>> not_checked{};
        std::vector<std::shared_ptr<puzzle>> all_puz{};
        std::vector<std::shared_ptr<puzzle>> children{};
        std::vector<std::shared_ptr<puzzle>> checked{};
        std::deque<std::shared_ptr<puzzle>> steps;
        void get_puzzle();
        void solvable();
        bool check(array puz) { return puz == target; }
        std::vector<std::shared_ptr<puzzle>> set_children(std::shared_ptr<puzzle> puz);
        void BFS_search();
        void DFS_search();
        void A_star_search();
        void show_steps();
        std::shared_ptr<puzzle> get_arr(){ return initial_puz;}
};
#endif