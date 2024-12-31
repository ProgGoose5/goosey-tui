#ifndef VARIABLES_H
#define VARIABLES_H

//We define the variables, the libs and the fuction that we will use in the program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "declarations.c"
#include <utf8/utf8.h>

//Variables
extern int actcaj;
extern int cajas;
extern char* apps[];
extern char* appsexe[];
extern int apps_layout;

//Functions
extern void Saving();
extern void Loading();
extern void ClearSaveFiles();
extern void Upperdecoration();
extern void KeyCommands();
#endif
