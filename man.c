#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "man.h"
#include "hand.h"

bool addrow(char *newline, int col, TABLE *tab)
{

    if (col != tab->col)
    {
        return false;
    }

    char ***newTabAr = crtabar(tab->row + 1, tab->col);
    tabcpy(tab, newTabAr);
    freetab(tab);
    tab->tabAr = newTabAr;

    char *rest;
    char *token;
    rest = newline;
    for (int j = 0; j < tab->col; j++)
    {
        token = strtok_r(rest, " ", &rest);
        tab->tabAr[tab->row][j] = (char *)malloc(sizeof(token));
        strcpy(tab->tabAr[tab->row][j], token);
    }
    tab->row++;

    return true;
}

bool addcol(char newline[], int row, TABLE *tab)
{
    if (row != tab->row)
    {
        return false;
    }

    char ***newTabAr = crtabar(tab->row, tab->col + 1);
    tabcpy(tab, newTabAr);
    freetab(tab);
    tab->tabAr = newTabAr;

    char *rest;
    char *token;
    rest = newline;
    for (int i = 0; i < tab->row; i++)
    {
        token = strtok_r(rest, " ", &rest);
        tab->tabAr[i][tab->col] = (char *)malloc(sizeof(token));
        strcpy(tab->tabAr[i][tab->col], token);
    }
    tab->col++;
    return true;
}

int colindex(char col[], TABLE *tab)
{
    for (int i = 0; i < tab->col; i++)
    {
        if (strcmp(tab->tabAr[0][i], col) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool strdigit(char *col)
{
    for (int i = 0; i < (int)strlen(col); i++)
    {
        if (isdigit(col[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

double average(char col[], TABLE *tab)
{
    int index = colindex(col, tab);

    double sum = 0;
    for (int i = 1; i < tab->row; i++)
    {
        if (strdigit(tab->tabAr[i][index]))
        {
            sum += atof(tab->tabAr[i][index]);
        }
    }
    return sum / tab->row;
}

double sumc(char col[], TABLE *tab)
{
    int index = colindex(col, tab);

    double sum = 0;
    for (int i = 1; i < tab->row; i++)
    {
        if (strdigit(tab->tabAr[i][index]))
        {
            sum += atof(tab->tabAr[i][index]);
        }
    }
    return sum;
}

double maximum(char col[], TABLE *tab)
{
    int index = colindex(col, tab);

    double max = 0;
    for (int i = 2; i < tab->row; i++)
    {
        if (max < atof(tab->tabAr[i][index]))
        {
            max = atof(tab->tabAr[i][index]);
        }
    }
    return max;
}

double minimum(char col[], TABLE *tab)
{
    int index = colindex(col, tab);

    double min = atof(tab->tabAr[1][index]);
    for (int i = 2; i < tab->row; i++)
    {
        if (min > atof(tab->tabAr[i][index]))
        {
            min = atof(tab->tabAr[i][index]);
        }
    }
    return min;
}