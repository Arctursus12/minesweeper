#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void map_setup_basic(int array[10][10]){
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            array[row][col] = 0;
        }
    }
    std::srand(std::time(0));
  
    int bomb_count = 0;
    while(bomb_count < 8){
        int random_row = std::rand() % 10;
        int random_col = std::rand() % 10;
        if(array[random_row][random_col] == 0){
            array[random_row][random_col] = -1;
            bomb_count++;
        }
    }
}

void display_temp(const int array[10][10]){
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            if(array[row][col] == -1) std::cout << 'X' << "\t";
            else std::cout << array[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

void add_adjacent_counts(int array[10][10]){
    int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Up, Down, Left, Right
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // Top-Left, Top-Right, Bottom-Left, Bottom-Right
    };
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            if(array[row][col] == -1){
                for(int i = 0; i < 8; ++i){
                    int newRow = row + directions[i][0];
                    int newCol = col + directions[i][1];
                    if(newRow >= 0 && newRow < 10 && newCol >= 0 && newCol < 10){
                        if(array[newRow][newCol] != -1){
                            array[newRow][newCol] += 1;
                        }
                    }
                }
            }
        }
    }
}