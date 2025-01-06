#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <wctype.h>

#ifndef DECLARATIONS_C

//Defining Pairs numbers.
#define UNSELECTED_PAIR 1
#define SELECTED_PAIR 2
#define BEAUTY_PAIR 3
#define BEAUTY1_PAIR 4

//Not customizable (Or atleast not recommendable)

int actcaj = 0; // ActCaj means Actual Box.
int cajas = 1; // Cajas means Boxes, where are stored the programs.
int boxeslines= 1; //Boxeslines means the different lines that the boxes can complete.

//Customizable
int gap= 3; 

//Not Customizable
int apps_layout; // Apps Layout is the number of apps per line.
int x, y, x2; //Positions on the terminal
int m=1;    //Also a position in the terminal.

//Not Customizable
char* apps[100] = {"EXIT"};
char* appsexe[100] = {"exit"};

//Customizable
char hordec[100] = "═"; // Horizontal Decoration
char sidedec[] =  "║"; // Side Decoration
char cornerdec1[]= "╔"; //Upper Left Corner
char cornerdec2[]= "╗"; //Upper Right Corner
char cornerdec3[]= "╚"; //Lower Left Corner
char cornerdec4[]= "╝"; //Lower Right Corner
char Selecteddecoration1[]= "►"; //Appears at the left when an app is hovered. 
char Selecteddecoration2[]= "◀"; //Same as Selected Decoration but at the Right.

//Function for loading saved apps
void Loading(char* local_apps[], char* local_appsexe[]) {
    char path1[256], path2[256], path3[256], path4[256];
    snprintf(path1, sizeof(path1), "%s/.config/goosey/apps.txt", getenv("HOME"));
    snprintf(path2, sizeof(path2), "%s/.config/goosey/executables.txt", getenv("HOME"));
    snprintf(path3, sizeof(path3), "%s/.config/goosey/cajas.txt", getenv("HOME"));
    snprintf(path4, sizeof(path4), "%s/.config/goosey/actcaj.txt", getenv("HOME"));

    FILE* file = fopen(path1, "r");
    FILE* file2 = fopen(path2, "r");
    FILE* file3 = fopen(path3, "r");
    FILE* file4 = fopen(path4, "r");
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

//Function for saving apps
void Saving(char* local_apps[], char* local_appsexe[]) {
    char path1[256], path2[256], path3[256], path4[256];
    snprintf(path1, sizeof(path1), "%s/.config/goosey/apps.txt", getenv("HOME"));
    snprintf(path2, sizeof(path2), "%s/.config/goosey/executables.txt", getenv("HOME"));
    snprintf(path3, sizeof(path3), "%s/.config/goosey/cajas.txt", getenv("HOME"));
    snprintf(path4, sizeof(path4), "%s/.config/goosey/actcaj.txt", getenv("HOME"));

    FILE* file = fopen(path1, "w");
    FILE* file2 = fopen(path2, "w");
    FILE* file3 = fopen(path3, "w");
    FILE* file4 = fopen(path4, "w");
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

//Function for Clearing Save Files
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

//Function for Defining or starting Processes.    
void Definitions(){
    
    initscr(); // Initialize the ncurses library
    start_color(); // Start color functionality

//Initializes the pairs, which are the combinations of colors.   
    init_pair(UNSELECTED_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(SELECTED_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BEAUTY_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(BEAUTY1_PAIR, COLOR_GREEN, COLOR_BLACK);
    
}


void Resizing(){
    //BASH COMMANDS
char lines[12]= "tput lines"; 
char columns[12]="tput cols"; 

//Defining variables to copy the result of the commands
int lns, cols;

FILE* lines_fp = popen(lines, "r"); //Calls the command into Bash and Reads the results.
FILE* columns_fp = popen(columns, "r"); //Same.

// Get the number of lines and columns
if(lns != LINES || cols != COLS){
    lns = LINES;
    cols = COLS;
     x2 = cols;
     x = (cols/2);
     y = lns;
}

apps_layout = x2/11; //You can change this for a better layout.

//Closing the Bash.
pclose(lines_fp); 
pclose(columns_fp);   
}

//Visual Function for Painting the entire terminal on Black.
void blackout(){
    for(int i=-2; i<=y; i++){
        for(int j=-2; j<=x2+2; j++){
            UNSELECTED_PAIR;
            mvprintw(i, j, " ");
        }
    }
}

//Visual Function for printing the buttons.
void buttonlay(){
    if(x2>70){
move (y-2, 3);
//F1 
attron(COLOR_PAIR(BEAUTY_PAIR));
printw("F1: ");
attron(COLOR_PAIR(SELECTED_PAIR));
printw("Remove Command\t");
//F2
attron(COLOR_PAIR(BEAUTY_PAIR));
printw("F2: ");
attron(COLOR_PAIR(SELECTED_PAIR));
printw("Add New Command\t");
//F3
attron(COLOR_PAIR(BEAUTY_PAIR));
printw("F3: ");
attron(COLOR_PAIR(SELECTED_PAIR));
printw("Execute Selected\t");
    }
}

void Upperdecoration(){
//Visual Function that prints the upper decoration.
    attron(COLOR_PAIR(BEAUTY_PAIR));
    mvprintw(0,1,"%s", cornerdec1);
        for(int i=0; i<x2-3; i++){
            printw("%s", hordec);
        }
        attron(COLOR_PAIR(UNSELECTED_PAIR));
        mvprintw(0,x-6,"Goosey"); 
        attron(COLOR_PAIR(BEAUTY_PAIR));
        mvprintw(0,x-7, "╣");
        mvprintw(0,x, "╠");
        mvprintw(0, x2-2,"%s", cornerdec2);
        move(0, x2 - 1);

        
}
//Visual Function that prints the sides decoration.
void Sidesdecoration(){
    attron(COLOR_PAIR(BEAUTY_PAIR));
    for(int y1=1; y1<y-1; y1++){
    mvprintw(y1, x2-2, "%s", sidedec);
    mvprintw(y1, 1, "%s", sidedec);
    }
    move(1, 4);
}

//Visual Function that prints the lower decoration.
void Lowerdecoration(){
    
    
    attron(COLOR_PAIR(BEAUTY_PAIR));
    mvprintw(y-1,1,"%s", cornerdec3);
        for(int i=2; i<x2-2; i++){
            
            mvprintw(y-1, i,"%s", hordec);
        }
        printw("%s", cornerdec4);
        printw("\n");
                
}

//Function for defining the keys and their commands.
void KeyCommands(){

        int cius = getch(); //Getch gets the input from the keyboard.
        char command[100];
        switch (cius) { //Cases for different Keys
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
                char new_app[100]; //declare a local variable for setting up apps.
                echo();
                getstr(new_app); //Get string new_app, gets the value of a character.
                noecho();
                apps[cajas] = strdup(new_app); //This same variable is copied into the string.

            //Same process
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

            case KEY_F(3):
                sprintf(command, "%s &", appsexe[actcaj]);
                system(command);
                break;

            case KEY_UP:
             if (actcaj>= apps_layout){
                actcaj-=apps_layout;
                }
                break;

            case KEY_DOWN:
            if (actcaj < cajas - apps_layout){
                actcaj+=apps_layout;
                }
                break;

            case KEY_F(1):
            if (cajas > 1){
        
                if(actcaj<cajas){

                    for(int i=1; i<cajas-actcaj; i++){
                       int j= i-1;
                char* temp_app = apps[actcaj+i];
                   apps[actcaj+j]= temp_app;
                char* temp_exe = appsexe[actcaj+i];
                   appsexe[actcaj+j] = temp_exe;
                   Saving(apps, appsexe);
                    }
                   cajas--;
                  
                }


            
            break;

            }
        }
}
#endif
