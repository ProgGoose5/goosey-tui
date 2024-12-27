#ifndef VARIABLES_H
#define VARIABLES_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

extern int actcaj;
extern int cajas;
extern char* apps[];
extern char* appsexe[];

extern void Saving(char* apps[], char* appsexe[]);
extern void Loading(char* apps[], char* appsexe[]);

#endif
