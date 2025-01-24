#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <vector>
#include "starter_array.h"
using namespace std;

TEST_CASE("Testing map_setup_basic: check number and positions of 'X's"){
    char grid[10][10];
    map_setup_basic(grid);
    int bomb_count = 0;
    std::set<std::pair<int, int>> bomb_positions;
    for(int row = 0; row < 10; ++row){
        for(int col = 0; col < 10; ++col){
            if(grid[row][col] == 'X'){
                bomb_count++;
                bomb_positions.insert({row, col});
            }
        }
    }
    CHECK(bomb_count == 8);
    CHECK(bomb_positions.size() == 8);
}