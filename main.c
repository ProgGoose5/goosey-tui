#include "variables.h"

int main() {

    initscr();
    start_color();
    //We define the combination of colors (Number, foreground, background);
    Definitions();
    keypad(stdscr, TRUE);
    noecho(); 
    Loading(apps, appsexe);
    

    while (1) { //Looped until the user closes the program.
    
    //Clearing Screen and printing the title...
        clear(); 
        Resizing();
        Upperdecoration();
        Lowerdecoration();
        Sidesdecoration();
        Saving(apps, appsexe);
        
        
        
        for ( int i = 0; i < cajas; i++) {
            if (i == actcaj) {
               attron(COLOR_PAIR(SELECTED_PAIR));
              
            } else {
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                
            }
            printw("%s", apps[i]);
            attron(COLOR_PAIR(UNSELECTED_PAIR));
            printw("\t");
            attron(COLOR_PAIR(BEAUTY1_PAIR));
            
            
        }
        attron(COLOR_PAIR(BEAUTY_PAIR));
        refresh();
        KeyCommands();
        
        
    }

    endwin();
    return 0;
}
