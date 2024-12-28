#include "variables.h"

#define UNSELECTED_PAIR 1
#define SELECTED_PAIR 2

int actcaj = 0;
int cajas = 2;
char* apps[]={ "firefox", "terminology" };
char* appsexe[]={ "firefox", "exec terminology" };

void Loading(char* local_apps[], char* local_appsexe[]) {
    attroff(COLOR_PAIR(UNSELECTED_PAIR)); 
    attroff(COLOR_PAIR(SELECTED_PAIR)); 
    FILE* file = fopen("apps.txt", "r");
    FILE* file2 = fopen("executables.txt", "r");
    if (file == NULL) {
        return;
    }
       if (file2 == NULL) {
        return;
    }


    fscanf(file, "%d", &cajas);
    fscanf(file, "%d", &actcaj);

    for (int i = 0; i < cajas; i++) {
        char app[100];
        fscanf(file, "%s", app);
        local_apps[i] = strdup(app);
    }

    for (int i = 0; i < cajas; i++) {
        char app[100];
        fscanf(file2, "%s", app);
        local_appsexe[i] = strdup(app);
    }
    fclose(file);
    fclose(file2);
}

void Saving(char* local_apps[], char* local_appsexe[]) {
     attroff(COLOR_PAIR(UNSELECTED_PAIR)); 
    attroff(COLOR_PAIR(SELECTED_PAIR)); 
    FILE* file = fopen("apps.txt", "w");
    FILE* file2 = fopen("executables.txt", "w");
    if (file == NULL) {
        return;
    }
    if (file2 == NULL) {
        return;
    }

    fprintf(file, "%d\n", cajas);
    fprintf(file, "%d\n", actcaj);
 
    fprintf(file2, "%d\n", cajas);
    fprintf(file2, "%d\n", actcaj);

    for (int i = 0; i < cajas; i++) {
        fprintf(file, "%s\n", local_apps[i]);
    }

    for (int i = 0; i < cajas; i++) {
        fprintf(file2, "%s\n", local_appsexe[i]);
    }
    fclose(file);
    fclose(file2);
}

int main() {
    initscr();
    start_color();
    init_pair(UNSELECTED_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECTED_PAIR, COLOR_BLACK, COLOR_WHITE);
    keypad(stdscr, TRUE);
    noecho(); 

    Loading(apps, appsexe);


    while (1) {
        clear();
        attron(COLOR_PAIR(UNSELECTED_PAIR));
        printw("TUI Bar \n"); 

        for ( int i = 0; i < cajas; i++) {
            
            if (i == actcaj) {
               attron(COLOR_PAIR(SELECTED_PAIR));
              
            } else {
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                
            }
          
            printw("%s \t ", apps[i]);
            
            
            
        }

        refresh();
        int cius = getch();
        char command[100];
        switch (cius) {
            case KEY_LEFT:
                if (actcaj > 0) {
                    actcaj--;
                }
                break;

            case KEY_RIGHT:
                if (actcaj < cajas - 1) {
                    actcaj++;
                }
                break;

            case KEY_UP:
            attron(COLOR_PAIR(UNSELECTED_PAIR));
                clear();
                printw("Write down Application Name: ");
                char new_app[100];
                echo();
                getstr(new_app);
                noecho();
                apps[actcaj + 1] = strdup(new_app);

                printw("Write down the executable: ");
                char new_app2[100];
                echo();
                getstr(new_app2);
                noecho();
                appsexe[actcaj + 1] = strdup(new_app2);
                cajas++;
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                Saving(apps, appsexe); 


                break;

            case KEY_DOWN:
                if (cajas > 1) {
                    cajas--;
                }
                break;
            case KEY_BACKSPACE:
                sprintf(command, "%s &", appsexe[actcaj]);
                system(command);
                continue;
        }
    }

    endwin();
    return 0;
}
