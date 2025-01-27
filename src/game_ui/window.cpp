#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array_grid_math.h"
using namespace std;

void initialize_colors(){
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
}

void reveal_adjacent(int row, int col, int grid[8][16], bool revealed[8][16], int rows, int cols) {
    if(row < 0 || row >= rows || col < 0 || col >= cols) return;
    if(revealed[row][col]) return;
    revealed[row][col] = true;
    if(grid[row][col] != 0) return;

    int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Up, Down, Left, Right
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // Top-Left, Top-Right, Bottom-Left, Bottom-Right
    };

    for(int i = 0; i < 8; ++i){
        reveal_adjacent(row + directions[i][0], col + directions[i][1], grid, revealed, rows, cols);
    }
}

int main(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    initialize_colors();

    const int rows = 8;
    const int cols = 16;
    int startx = 0, starty = 0;
    int box_height = 2, box_width = 4;
    int spacing = 1; 
    int current_row = 0, current_col = 0;
    int grid[rows][cols];
    bool revealed[rows][cols] = {{false}};
    bool game_over = false;
    bool game_won = false;
    int non_bomb_cells = rows * cols - 8;

    map_setup_basic(grid);
    add_adjacent_counts(grid);

    WINDOW *win = newwin(rows * (box_height + spacing) + 1,
                         cols * (box_width + spacing) + 1, starty, startx);
                         
    int ch;
    while((ch=getch()) != 'q'){
        if(ch != ERR && !game_over && !game_won){
            switch(ch){
                case KEY_UP: current_row = (current_row > 0) ? current_row - 1 : current_row; break;
                case KEY_DOWN: current_row = (current_row < rows - 1) ? current_row + 1 : current_row; break;
                case KEY_LEFT: current_col = (current_col > 0) ? current_col - 1 : current_col; break;
                case KEY_RIGHT: current_col = (current_col < cols - 1) ? current_col + 1 : current_col; break;
                case 10: // Enter key
                    if(grid[current_row][current_col] == -1){
                        game_over = true;
                    } else if(!revealed[current_row][current_col]){
                        reveal_adjacent(current_row, current_col, grid, revealed, rows, cols);
                        non_bomb_cells--;
                        if(non_bomb_cells == 0){
                            game_won = true;
                        }
                    }
                    break;
            }
        }
        for(int row=0; row<rows; ++row){
            for(int col=0; col<cols; ++col){
                int start_y = row * (box_height + spacing);
                int start_x = col * (box_width + spacing);
                
                if(game_won){
                    wattron(win, COLOR_PAIR(5));
                } else if(game_over){
                    wattron(win, COLOR_PAIR(4));
                } else if(row == current_row && col == current_col){
                    wattron(win, COLOR_PAIR(2));
                } else if(revealed[row][col]){
                    wattron(win, COLOR_PAIR(3));
                } else {
                    wattron(win, COLOR_PAIR(1));
                }
                
                mvwaddch(win, start_y, start_x, ACS_ULCORNER);
                mvwaddch(win, start_y + box_height, start_x, ACS_LLCORNER);
                mvwaddch(win, start_y, start_x + box_width, ACS_URCORNER);
                mvwaddch(win, start_y + box_height, start_x + box_width, ACS_LRCORNER);
                mvwhline(win, start_y, start_x + 1, ACS_HLINE, box_width - 1);
                mvwhline(win, start_y + box_height, start_x + 1, ACS_HLINE, box_width - 1);
                mvwvline(win, start_y + 1, start_x, ACS_VLINE, box_height - 1);
                mvwvline(win, start_y + 1, start_x + box_width, ACS_VLINE, box_height - 1);
                
                if(revealed[row][col] || game_over){
                    if(grid[row][col] == -1)
                        mvwprintw(win, start_y + box_height / 2, start_x + box_width / 2, "X");
                    else if(grid[row][col] > 0)
                        mvwprintw(win, start_y + box_height / 2, start_x + box_width / 2, "%d", grid[row][col]);
                }
                
                wattroff(win, COLOR_PAIR(1));
                wattroff(win, COLOR_PAIR(2));
                wattroff(win, COLOR_PAIR(3));
                wattroff(win, COLOR_PAIR(4));
                wattroff(win, COLOR_PAIR(5));
            }
        }
        wrefresh(win);
    }
    endwin();
    return 0;
}