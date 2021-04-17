#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "man.h"
#include "hand.h"

int main(int argc, char const *argv[])
{

    char *input = (char *)malloc(sizeof(char) * 50);
    char *output = (char *)malloc(sizeof(char) * 50);
    char *errmes = (char *)malloc(sizeof(char) * 50);

    FILE *csv;

    if (argcheck(argc, argv, input, output, errmes))
    {
        printf("%s\n", errmes);
        exit(1);
    }

    if (iscsv(input) && iscsv(output))
    {
        csv = fopen(input, "r");
        if (csv == NULL)
        {
            printf("Soubor %s se nepodařilo otevřít.\n", input);
            exit(1);
        }
    }
    else if (iscsv(input))
    {
        printf("Nesprávný typ souboru %s.\n", output);
        exit(1);
    }
    else
    {
        printf("Nesprávný typ souboru %s.\n", input);
        exit(1);
    }
    

    TABLE *tab = crtab(csv);
    load(csv, tab);

    printf("Soubor: %s, řádky: %d, sloupce: %d\n", input, tab->row, tab->col);

    bool cont = true;
    char *cmd;
    char buffer[101];
    char *values;
    while (cont)
    {
        printf("Zadejte příkaz: ");
        scanf("%s", buffer);
        cmd = (char *)malloc(strlen(buffer) + 1);
        strcpy(cmd, buffer);

        if (strcmp(cmd, "exit") != 0)
        {
            scanf(" %100[^\n]", buffer);
            values = (char *)malloc(strlen(buffer) + 1);
            strcpy(values, buffer);
        }
        switch (cmdeval(cmd))
        {
        case 1:
            if (addrow(values, numval(values), tab))
            {
                puts("Řádek byl přidán");
            }
            else
            {
                puts("Nesprávný počet sloupců");
            }
            break;
        case 2:
            if (addcol(values, numval(buffer), tab))
            {
                puts("Sloupec byl přidán");
            }
            else
            {
                puts("Nesprávný počet řádků!");
            }
            break;
        case 3:
            if (colindex(values, tab) == -1)
            {
                puts("Zadaný sloupec neexistuje!");
            }
            else
            {
                printf("Průměr sloupce %s: %.2f\n", values, average(values, tab));
            }
            break;
        case 4:
            if (colindex(values, tab) == -1)
            {
                puts("Zadaný sloupec neexistuje!");
            }
            else
            {
                printf("Maximum sloupce %s: %.2f\n", values, maximum(values, tab));
            }
            break;
        case 5:
            if (colindex(values, tab) == -1)
            {
                puts("Zadaný sloupec neexistuje!");
            }
            else
            {
                printf("Minimum sloupce %s: %.2f\n", values, minimum(values, tab));
            }

            break;
        case 6:
            if (colindex(values, tab) == -1)
            {
                puts("Zadaný sloupec neexistuje!");
            }
            else
            {
                printf("Suma sloupce %s: %.2f\n", values, sumc(values, tab));
            }
            break;
        case 7:
            save(output, tab);
            printf("Ukladam do souboru %s\n", output);
            cont = false;
            break;
        default:
            puts("Neznámý příkaz");
            break;
        }
        free(cmd);
        if (cont)
        {
            free(values);
        }
    }

    free(input);
    free(output);
    free(errmes);

    fclose(csv);

    return 0;
}
