#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <utf8/utf8.h>
#include <locale.h>

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
int apps_layout; // Apps Layout is the number of apps per line.
int x, y, x2;

char hordec[100] = "~"; // Horizontal Decoration
char sidedec[50]= "|"; // Side Decoration

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
    setlocale(LC_ALL, ""); 
    init_pair(UNSELECTED_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECTED_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(BEAUTY_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(BEAUTY1_PAIR, COLOR_GREEN, COLOR_BLACK);

}

void Resizing(){
char lines[12]= "tput lines";
char columns[12]="tput cols";

int lns, cols;

FILE* lines_fp = popen(lines, "r");
FILE* columns_fp = popen(columns, "r");

if(lns != LINES || cols != COLS){
    lns = LINES;
    cols = COLS;
     x2 = cols;
     x = (cols/2);
     y = lns;
}

apps_layout = x;

pclose(lines_fp);
pclose(columns_fp);   
// Set the font style and size using system commands
char font_command[100];
//sprintf(font_command, "echo -ne '\\e]710;%s\\007'", "xft:Fira Code:style=Regular:pixelsize=12");
//system(font_command);
}

void Upperdecoration(){
    
    attron(COLOR_PAIR(BEAUTY_PAIR));
    printw("*");
        for(int i=0; i<x2-3; i++){
            printw("%s", hordec);
        }
        attron(COLOR_PAIR(UNSELECTED_PAIR));
        mvprintw(0,x-3,"Goosey"); 
        attron(COLOR_PAIR(BEAUTY_PAIR));

        mvprintw(0, x2-2,"*");
        move(0, x2 - 1);

        
}

void Sidesdecoration(){
    attron(COLOR_PAIR(BEAUTY_PAIR));
    for(int y1=1; y1<y-1; y1++){
    mvprintw(y1, x2-2, sidedec);
    mvprintw(y1, 0, sidedec);
    }
    move(1, 2);
}

void Lowerdecoration(){
    
    
    attron(COLOR_PAIR(BEAUTY_PAIR));
    mvprintw(y-1,0,"*");
        for(int i=1; i<x2-2; i++){
            
            mvprintw(y-1, i,"%s", hordec);
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

