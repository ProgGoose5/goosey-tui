#include "variables.h"

int actcaj = 0;
int cajas = 2;
char* apps[]={ "firefox", "terminology" };
char* appsexe[]={ "firefox", "exec terminology" };

void Loading(char* local_apps[], char* local_appsexe[]) {
    FILE* file = fopen("apps.txt", "r");
    if (file == NULL) {
        return;
    }

    fscanf(file, "%d", &cajas);
    fscanf(file, "%d", &actcaj);

    for (int i = 0; i < cajas; i++) {
        char app[50];
        fscanf(file, "%s", app);
        local_apps[i] = strdup(app);
    }

    for (int i = 0; i < cajas; i++) {
        char app[50];
        fscanf(file, "%s", app);
        local_appsexe[i] = strdup(app);
    }
    fclose(file);
}

void Saving(char* local_apps[], char* local_appsexe[]) {
    FILE* file = fopen("apps.txt", "w");
    if (file == NULL) {
        return;
    }

    fprintf(file, "%d\n", cajas);
    fprintf(file, "%d\n", actcaj);

    for (int i = 0; i < cajas; i++) {
        fprintf(file, "%s\n", local_apps[i]);
    }

    for (int i = 0; i < cajas; i++) {
        fprintf(file, "%s\n", local_appsexe[i]);
    }
    fclose(file);
}

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho(); 

    Loading(apps, appsexe);


    while (1) {
        clear();
        printw("TUI Bar \n"); 

        for ( int i = 0; i < cajas; i++) {
            printw("%s", apps[i]);
            if (i == actcaj) {
                printw("<< \t ");
            } else {
                printw("\t \t");
            }
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
                clear();
                printw("Write down Application Name: ");
                char new_app[50];
                echo();
                getstr(new_app);
                noecho();
                apps[actcaj + 1] = strdup(new_app);

                printw("Write down the executable: ");
                char new_app2[50];
                echo();
                getstr(new_app2);
                noecho();
                appsexe[actcaj + 1] = strdup(new_app2);
                cajas++;
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