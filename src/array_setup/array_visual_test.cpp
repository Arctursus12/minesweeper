#include "array_grid_math.h"

int main(){
    int array[10][10];
    map_setup_basic(array);
    add_adjacent_counts(array);
    display_temp(array);
    return 0;
}