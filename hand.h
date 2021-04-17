#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#include "man.h"

bool argcheck(int argc, char const *argv[], char *input, char *output, char *errmes );

bool iscsv(char *fname);

const char *getext(const char *fname);

int cmdeval(char cmd[]);
