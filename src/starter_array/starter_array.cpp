#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void map_setup_basic(char array[10][10]){
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            array[row][col] = '-';
        }
    }
    std::srand(std::time(0));

    int bomb_count = 0;
    while(bomb_count < 8){
        int random_row = std::rand() % 10;
        int random_col = std::rand() % 10;
        if(array[random_row][random_col] == '-'){
            array[random_row][random_col] = 'X';
            bomb_count++;
        }
    }
}

void display_temp(const char array[10][10]){
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            std::cout << array[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}