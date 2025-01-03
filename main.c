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
        boxeslines=1;
        
        
        for ( int i = 0; i < cajas; i++) {
            if (i == actcaj) {
               attron(COLOR_PAIR(SELECTED_PAIR));
              
            } else {
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                
            }

char* localcar= apps[i];
            int numeric_value = 0;
            for (char* p = localcar; *p != '\0'; p++) {
                numeric_value += *p;
                numeric_value *=gap;
            }

            if(i/boxeslines==apps_layout){
                
                move(m+cajas/i, 2);
                boxeslines++;
            }
            move(m, numeric_value);
            printw("%s", apps[i]);
            for(int h=0; h<gap; h++){
            printw(" ");    
            attron(COLOR_PAIR(UNSELECTED_PAIR));
            }
            // Keep it within a single digit
            
            attron(COLOR_PAIR(BEAUTY1_PAIR));
            
            
        }
        attron(COLOR_PAIR(BEAUTY_PAIR));
        refresh();
        KeyCommands();
        
        
    }

    endwin();
    return 0;
}
