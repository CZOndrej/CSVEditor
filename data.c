
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "man.h"
#include "hand.h"

TABLE *crtab(FILE *csv)
{
    TABLE *tab = (TABLE *)malloc(sizeof(TABLE));
    tab->row = filerow(csv);
    tab->col = filecol(csv);
    tab->tabAr = crtabar(tab->row, tab->col);
    return tab;
}

char ***crtabar(int row, int col)
{

    char ***tabAr = (char ***)malloc(sizeof(char **) * row);
    for (int i = 0; i < row; i++)
        tabAr[i] = (char **)malloc(sizeof(char *) * col);
    return tabAr;
}

void freetab(TABLE *tab)
{
    for (int i = 0; i < tab->row; i++)
    {
        for (int j = 0; j < tab->col; j++)
        {
            free(tab->tabAr[i][j]);
        }
    }
    for (int i = 0; i < tab->row; i++)
    {
        free(tab->tabAr[i]);
    }
    free(tab->tabAr);
}

int filecol(FILE *csv)
{
    fseek(csv, 0, SEEK_SET);
    char row[1001];
    fscanf(csv, "%s", row);
    int cols = 0;
    /*char *token;
    char *rest = row;
    int cols = 0;
    while ((token = strtok_r(rest, ",", &rest)))
    {
        cols++;
    }
    return cols;*/
    bool sw = true;

    for (int i = 0; i < (int)strlen(row); i++)
    {

        if (row[i] == '\"' && sw)
        {
            sw = false;
        }
        else if (row[i] == '\"')
        {
            sw = true;
        }
        if (row[i] == ',' && sw)
        {
            cols++;
        }
    }
    return cols + 1;
}

int filerow(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    int pocet = 0;
    char buf[1024];
    while (fscanf(file, " %[^\n]", buf) != EOF)
    {
        pocet++;
    }
    return pocet;
}

void load(FILE *file, TABLE *tab)
{
    fseek(file, 0, SEEK_SET);

    /*char row[100];
    char *rest;
    char *token;
    for (int i = 0; i < tab->row; i++)
    {
        fscanf(file, "%s", row);
        rest = row;
        for (int j = 0; j < tab->col; j++)
        {
            token = strtok_r(rest, ",", &rest);
            tab->tabAr[i][j] = (char *)malloc(sizeof(token));
            strcpy(tab->tabAr[i][j], token);
        }
    }*/

    char buffer[1001];
    char cellbuf[501];
    int index = 0;
    bool sw = true;
    int row = 0;
    int col = 0;
    while (fscanf(file, " %1000[^\n]", buffer) != EOF)
    {

        for (int j = 0; j < (int)strlen(buffer) + 1; j++)
        {
            sw = switcher(buffer[j], sw);
            if (sw)
            {
                if (buffer[j] == ',' || j == (int)strlen(buffer))
                {

                    cellbuf[index] = '\0';
                    index = 0;
                    tab->tabAr[row][col] = (char *)malloc(strlen(cellbuf) + 1);
                    strcpy(tab->tabAr[row][col], cellbuf);
                    col++;
                }
                else
                {
                    cellbuf[index] = buffer[j];
                    index++;
                }
            }
            else
            {
                cellbuf[index] = buffer[j];
                index++;
            }
        }
        col = 0;
        row++;
    }
}

bool switcher(char c, bool s)
{
    if (c == '\"' && s)
    {
        return false;
    }
    else if (c == '\"')
    {
        return true;
    }
}

void printab(TABLE *tab)
{
    for (int i = 0; i < tab->row; i++)
    {
        for (int j = 0; j < tab->col; j++)
        {
            printf("%s ", tab->tabAr[i][j]);
        }
        puts("\n");
    }
}

void save(char *path, TABLE *tab)
{
    FILE *out = fopen(path, "w");

    for (int i = 0; i < tab->row; i++)
    {
        for (int j = 0; j < tab->col; j++)
        {
            if (j < (tab->col - 1))
            {
                fprintf(out, "%s,", tab->tabAr[i][j]);
            }
            else
            {
                fprintf(out, "%s\n", tab->tabAr[i][j]);
            }
        }
    }
    fclose(out);
    freetab(tab);
    free(tab);
}

void tabcpy(TABLE *tab, char ***newtab)
{
    for (int i = 0; i < tab->row; i++)
    {
        for (int j = 0; j < tab->col; j++)
        {
            newtab[i][j] = (char *)malloc(strlen(tab->tabAr[i][j]) + 1);
            strcpy(newtab[i][j], tab->tabAr[i][j]);
        }
    }
}

int numval(char str[])
{
    bool sw = true;
    int cols = 0;
    for (int i = 0; i < (int)strlen(str); i++)
    {

        if (str[i] == '\"' && sw)
        {
            sw = false;
        }
        else if (str[i] == '\"')
        {
            sw = true;
        }
        if (str[i] == ' ' && sw)
        {
            cols++;
        }
    }
    return cols + 1;
}
