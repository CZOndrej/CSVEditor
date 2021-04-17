#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    int row;
    int col;
    char ***tabAr;
} TABLE;

TABLE *crtab(FILE *csv);

char ***crtabar(int row, int col);

void freetab(TABLE *tab);

int filecol(FILE *csv);

int filerow(FILE *file);

void load(FILE *file, TABLE *tab);

bool switcher(char c, bool s);

void printab(TABLE *tab);

void save(char *path, TABLE *tab);

void tabcpy(TABLE *tab, char ***newtab);

int numval(char str[]);