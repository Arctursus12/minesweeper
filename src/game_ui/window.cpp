#include <ncurses.h>

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
    int box_height = 5, box_width = 10;
    int spacing = 1;  // Reduced spacing between boxes
    int current_row = 0, current_col = 0;

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
                
                // Draw the full box
                mvwaddch(win, start_y, start_x, ACS_ULCORNER);
                mvwaddch(win, start_y + box_height, start_x, ACS_LLCORNER);
                mvwaddch(win, start_y, start_x + box_width, ACS_URCORNER);
                mvwaddch(win, start_y + box_height, start_x + box_width, ACS_LRCORNER);
                mvwhline(win, start_y, start_x + 1, ACS_HLINE, box_width - 1);
                mvwhline(win, start_y + box_height, start_x + 1, ACS_HLINE, box_width - 1);
                mvwvline(win, start_y + 1, start_x, ACS_VLINE, box_height - 1);
                mvwvline(win, start_y + 1, start_x + box_width, ACS_VLINE, box_height - 1);
                
                wattroff(win, COLOR_PAIR(1));
                wattroff(win, COLOR_PAIR(2));
            }
        }

        wrefresh(win);
    }
    
    endwin();
    return 0;
}