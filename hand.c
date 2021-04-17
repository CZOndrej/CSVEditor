#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "man.h"
#include "hand.h"

bool argcheck(int argc, char const *argv[], char *input, char *output, char *errmes)
{
    if (argc == 5)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strncmp(argv[i], "-", 1) == 0)
            {
                if (strlen(argv[i]) == 2)
                {
                    switch (argv[i][1])
                    {
                    case 'i':
                        strcpy(input, argv[i + 1]);
                        break;
                    case 'o':
                        strcpy(output, argv[i + 1]);
                        break;
                    default:
                        sprintf(errmes, "Neznámý přepínač %s", argv[i]);
                        return true;
                        break;
                    }
                }
                else
                {
                    sprintf(errmes, "Neznámý přepínač %s", argv[i]);
                    return true;
                }
            }
        }
    }
    else
    {
        sprintf(errmes, "Nesprávný počet argumentů");
        return true;
    }
    return false;
}

bool iscsv(char *fname)
{
    char suf[] = "csv";
    if (strcmp(suf, getext(fname)) == 0)
    {
        return true;
    }
    return false;
}

const char *getext(const char *fname)
{
    const char *dot = strrchr(fname, '.');
    if (!dot || dot == fname)
    {
        return "";
    }
    return dot + 1;
}

int cmdeval(char cmd[])
{
   if(strcmp(cmd, "addrow") == 0)
   {
       return 1;
   }
   else if(strcmp(cmd, "addcol") == 0)
   {
       return 2;
   }
   else if(strcmp(cmd, "average") == 0)
   {
       return 3;
   }
   else if(strcmp(cmd, "max") == 0)
   {
       return 4;
   }
   else if(strcmp(cmd, "min") == 0)
   {
       return 5;
   }
   else if(strcmp(cmd, "sum") == 0)
   {
       return 6;
   }
   else if(strcmp(cmd, "exit") == 0)
   {
       return 7;
   }
   else
   {
       return -1;
   }
   
}