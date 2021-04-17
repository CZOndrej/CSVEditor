#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"

bool addrow(char *newline, int col, TABLE *tab);

bool addcol(char newline[], int row, TABLE *tab);

int colindex(char col[], TABLE *tab);

bool strdigit(char *col);

double average(char col[], TABLE *tab);

double sumc(char col[], TABLE *tab);

double maximum(char col[], TABLE *tab);

double minimum(char col[], TABLE *tab);
