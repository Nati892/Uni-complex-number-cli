/*Header file syntaxhandle.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*funtion prototypes*/
int isWhiteChar(char);/**/
int checkFloatParam(char *); 
float extractFloatParam(char *);
char extractCompParam(char *);
int countCommas(char *);/**/
void removeComma(char *);/**/
int checkResidualText(char *);/**/
int isLastEOF(char*);/**/
int isOnlyWhiteChars(char *);/**/
int isOnlyEOF(char *);/**/

enum CompParam
{
    BadInput,
    Acomp = 65,
    Bcomp,
    Ccomp,
    Dcomp,
    Ecomp,
    Fcomp
};

/*macros*/
#define dotChar 46
#define commaChar 44
#define newLineChar 10
#define underScoreChar '_'
#define plusChar '+'
#define minusChar '-'
