#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <vector>
#include <set>
#include "array_grid_math_TESTCOPY.h"

TEST_CASE("Testing map_setup_basic: check number and positions of bombs"){
    int grid[8][16];
    map_setup_basic(grid);
    int bomb_count = 0;
    std::set<std::pair<int, int>> bomb_positions;
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 16; ++col){
            if(grid[row][col] == -1){
                bomb_count++;
                bomb_positions.insert({row, col});
            }
        }
    }
    CHECK(bomb_count == 12);
    CHECK(bomb_positions.size() == 12);
}