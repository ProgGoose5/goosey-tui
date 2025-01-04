#ifndef VARIABLES_H
#define VARIABLES_H

//We define the variables, the libs and the fuction that we will use in the program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <wctype.h>
#include "declarations.c"
#include <locale.h>

//Variables
extern int actcaj;
extern int cajas;
extern int apps_layout;
extern int cius;
extern int x, y, x2, m;

extern char* apps[];
extern char* appsexe[];

extern char hordec[];
extern char Selecteddecoration1[];
extern char Selecteddecoration2[];
extern char cornerdec1[];
extern char cornerdec2[];
extern char cornerdec3[];
extern char cornerdec4[];

//Functions
extern void Saving();
extern void Loading();
extern void ClearSaveFiles();
extern void Upperdecoration();
extern void KeyCommands();
extern void Resizing();
extern void Lowerdecoration();
extern void Sidesdecoration();
extern void Definitions();
extern void Upperdecoration();

#endif
