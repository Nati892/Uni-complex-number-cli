/*header file for mycomp.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "syntaxhandle.h"

/*function prototypes*/
void initialize_numbers(complex *);
void GetInputLoop();
char *getNewLine();
void handleLine(char *);
int extractCommand(char *);
int handlecommandname(char *, char *);
int SearchCommand(char *);
int charToComplexindex(char );

enum commandName
{
    UNRECOGNIZED,
    READ_COMP,
    ADD_COMP,
    SUB_COMP,
    MULT_COMP_REAL,
    MULT_COMP_IMG,
    MULT_COMP_COMP,
    PRINT_COMP,
    ABS_COMP,
    STOP
};
/*macros*/
#define numberOfComplexVariables 6

/*array storing the complex variales*/
complex myNumbers[numberOfComplexVariables];
