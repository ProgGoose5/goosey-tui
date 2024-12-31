#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#ifndef DECLARATIONS_C

//Defining Pairs numbers.
#define UNSELECTED_PAIR 1
#define SELECTED_PAIR 2
#define BEAUTY_PAIR 3
#define BEAUTY1_PAIR 4

#define COLOR1 1

#define ADD_KEY 0667
#define RUN_KEY 0450
#define KEY_REMOVE 0666

int actcaj = 0; // ActCaj means Actual Box.
int cajas = 1; // Cajas means Boxes, where are stored the programs.

char* apps[100] = {"EXIT"};
char* appsexe[100] = {"exit"};
int apps_layout = 5; // Apps Layout is the number of apps per line.

void Loading(char* local_apps[], char* local_appsexe[]) {
    FILE* file = fopen("apps.txt", "r");
    FILE* file2 = fopen("executables.txt", "r");
    FILE* file3 = fopen("cajas.txt", "r");
    FILE* file4 = fopen("actcaj.txt", "r");

    if (file == NULL || file2 == NULL || file3 == NULL || file4 == NULL) {
        if (file != NULL) fclose(file);
        if (file2 != NULL) fclose(file2);
        if (file3 != NULL) fclose(file3);
        if (file4 != NULL) fclose(file4);
        return;
    }

    if (fscanf(file3, "%d", &cajas) != 1 || fscanf(file4, "%d", &actcaj) != 1) {
        fclose(file);
        fclose(file2);
        fclose(file3);
        fclose(file4);
        return;
    }

    for (int i = 0; i < cajas; i++) {
        char app[100];
        if (fscanf(file, "%99s", app) != 1) {
            break;
        }
        local_apps[i] = strdup(app);
    }

    for (int j = 0; j < cajas; j++) {
        char app[100];
        if (fscanf(file2, "%99s", app) != 1) {
            break;
        }
        local_appsexe[j] = strdup(app);
    }

    fclose(file);
    fclose(file2);
    fclose(file3);
    fclose(file4);
}

void Saving(char* local_apps[], char* local_appsexe[]) {
    FILE* file = fopen("apps.txt", "w");
    FILE* file2 = fopen("executables.txt", "w");
    FILE* file3 = fopen("cajas.txt", "w");
    FILE* file4 = fopen("actcaj.txt", "w");
    if (file == NULL || file2 == NULL || file3 == NULL || file4 == NULL) {
        if (file != NULL) fclose(file);
        if (file2 != NULL) fclose(file2);
        if (file3 != NULL) fclose(file3);
        if (file4 != NULL) fclose(file4);
        return;
    }

    fprintf(file3, "%d\n", cajas);
    fprintf(file4, "%d\n", actcaj);

    for (int i = 0; i < cajas; i++) {
        fprintf(file, "%s\n", local_apps[i]);
    }

    for (int i = 0; i < cajas; i++) {
        fprintf(file2, "%s\n", local_appsexe[i]);
    }

    fclose(file);
    fclose(file2);
    fclose(file3);
    fclose(file4);
}

void ClearSaveFiles() {
    FILE* file = fopen("apps.txt", "w");
    FILE* file2 = fopen("executables.txt", "w");
    FILE* file3 = fopen("cajas.txt", "w");
    FILE* file4 = fopen("actcaj.txt", "w");
    if (file != NULL) fclose(file);
    if (file2 != NULL) fclose(file2);
    if (file3 != NULL) fclose(file3);
    if (file4 != NULL) fclose(file4);
} 

void Definitions(){
    //initialization of colors, You can change the rgb tho.
    init_color(COLOR1, 255, 193, 23);
    
    init_pair(UNSELECTED_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECTED_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(BEAUTY_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(BEAUTY1_PAIR, COLOR_GREEN, COLOR_BLACK);

}

void Upperdecoration(){
    attron(COLOR_PAIR(UNSELECTED_PAIR));
    printw("*");
        for(int i=0; i<30; i++){
            printw("\u2501");
        }
        attron(COLOR_PAIR(UNSELECTED_PAIR));
        printw("Goosey!"); 
        attron(COLOR_PAIR(BEAUTY_PAIR));
        for(int i=0; i<30; i++){
            printw("\u2501");
        }
        printw("*");
        printw("\n");

        
}

void KeyCommands(){

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

            case KEY_F(2):
            
            attron(COLOR_PAIR(UNSELECTED_PAIR));
                clear();
                printw("Write down Application Name: ");
                char new_app[100];
                echo();
                getstr(new_app);
                noecho();
                apps[cajas] = strdup(new_app);

                printw("Write down the executable: ");
                char new_app2[100];
                echo();
                getstr(new_app2);
                noecho();
                appsexe[cajas] = strdup(new_app2);
                cajas++;
                attron(COLOR_PAIR(UNSELECTED_PAIR));
                Saving(apps, appsexe); 


                break;

            case KEY_F(1):
                if (cajas > 1) {
                    cajas--;
                }
                break;
            case KEY_F(3):
                sprintf(command, "%s &", appsexe[actcaj]);
                system(command);
                break;

            case KEY_DOWN:
             if (actcaj>= apps_layout){
                actcaj-=apps_layout;
                }
                break;

            case KEY_UP:
            if (actcaj <= cajas - apps_layout){
                actcaj+=apps_layout;
                }
                break;
        }
}

#endif
