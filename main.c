#include "variables.h"

int main() {
setlocale(LC_ALL, "");
    //We define the combination of colors (Number, foreground, background);
    Definitions();
    keypad(stdscr, TRUE);
    noecho(); 
    Loading(apps, appsexe);
    
    

    while (1) { //Looped until the user closes the program.
    
    //Clearing Screen and printing the title...
        clear(); 
        blackout();       
        Resizing();
        Upperdecoration();
        Lowerdecoration();
        buttonlay();
        Sidesdecoration();
        Saving(apps, appsexe);
        boxeslines=1;
        
        
        for ( int i = 0; i < cajas; i++) {
            if (i == actcaj) {
               attron(COLOR_PAIR(SELECTED_PAIR));
               printw("%s", Selecteddecoration1);
               
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

         if (i == actcaj) {
               attron(COLOR_PAIR(SELECTED_PAIR));
               printw(Selecteddecoration2);
               
            } else {
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                
            } 

            for(int h=0; h<gap; h++){
            printw(" ");    
            attron(COLOR_PAIR(UNSELECTED_PAIR));
            }
            
            
            attron(COLOR_PAIR(BEAUTY1_PAIR));
                        
        }
        attron(COLOR_PAIR(BEAUTY_PAIR));
        refresh();
        KeyCommands();                
    }

    endwin();
    return 0;
}
