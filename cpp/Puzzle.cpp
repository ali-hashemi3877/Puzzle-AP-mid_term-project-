#include <iostream>
#include <array>


std::array<std::array<int, 3>, 3> get_puzzle(){
    std::array<std::array<int, 3>, 3> arr = {};
    for (size_t i{}; i < 3; i++)
        for (size_t j{}; j < 3; j++)
            std::cin >> arr[i][j];
    return arr;
}

void show_puzzle(std::array<std::array<int, 3>, 3> arr){
    for (size_t i{}; i < 3; i++){
        for (size_t j{}; j < 3; j++)
            std::cout<< arr[i][j] << " ";
        std::cout<< std::endl;
    }
}