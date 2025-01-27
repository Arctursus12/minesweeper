#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array_grid_math.h>
using namespace std;

void map_setup_basic(int array[10][10]);
void add_adjacent_counts(int array[10][10]);

void initialize_colors(){
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

int main(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    
    initialize_colors();

    int grid_size = 10; 
    int startx = 0, starty = 0;
    int box_height = 3, box_width = 6;
    int spacing = 1;
    int current_row = 0, current_col = 0;
    int grid[10][10];

    map_setup_basic(grid);
    add_adjacent_counts(grid);

    WINDOW *win = newwin(grid_size * (box_height + spacing) + 1,
                         grid_size * (box_width + spacing) + 1, starty, startx);

    int ch; // Code made fully with "external" assistance, as I was extremely unsure on how to handle the input lag
    while((ch=getch()) != 'q'){
        if(ch != ERR){
            switch(ch){
                case KEY_UP: current_row = (current_row > 0) ? current_row - 1 : current_row; break;
                case KEY_DOWN: current_row = (current_row < grid_size - 1) ? current_row + 1 : current_row; break;
                case KEY_LEFT: current_col = (current_col > 0) ? current_col - 1 : current_col; break;
                case KEY_RIGHT: current_col = (current_col < grid_size - 1) ? current_col + 1 : current_col; break;
            }
        }
        
        for(int row=0; row<grid_size; ++row){
            for(int col=0; col<grid_size; ++col){
                int start_y = row * (box_height + spacing);
                int start_x = col * (box_width + spacing);
                
                if(row == current_row && col == current_col){
                    wattron(win, COLOR_PAIR(2));
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
                
                if(grid[row][col] == -1)
                    mvwprintw(win, start_y + box_height / 2, start_x + box_width / 2, "X");
                else if(grid[row][col] > 0)
                    mvwprintw(win, start_y + box_height / 2, start_x + box_width / 2, "%d", grid[row][col]);
                
                wattroff(win, COLOR_PAIR(1));
                wattroff(win, COLOR_PAIR(2));
            }
        }

        wrefresh(win);
    }
    
    endwin();
    return 0;
}