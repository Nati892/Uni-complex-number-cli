/*this file holds many useful functions for pasring text in mycomp*/

#include "syntaxhandle.h"

/*this function is called only after knowing that there is a valid float to convert.
The function extracts it from the string, deletes it from the start and returns it as a float value.*/
float extractFloatParam(char *LinePointer)
{
    char *Myfloat;
    char current;
    int i = 0, j, floatlength = 0, Linelength;
    float result;
    Linelength = strlen(LinePointer);
    current = LinePointer[i];

    while (isWhiteChar(current)) /*skip white chars before the float num*/
    {
        i++;
        current = LinePointer[i];
    }

    Myfloat = (char *)malloc(floatlength);                              /*store float string in Myfloat*/
    while (!isspace(current) && current != commaChar && current != EOF) /*extract the float variable to a string*/
    {
        i++;
        floatlength++;
        Myfloat = realloc(Myfloat, floatlength);

        Myfloat[floatlength - 1] = current;
        current = LinePointer[i];
    }

    floatlength++; /*add a \0 in the end of the float string*/
    Myfloat = realloc(Myfloat, floatlength);
    Myfloat[floatlength - 1] = '\0';

    result = (float)atof(Myfloat); /*convert to actual float*/
    Linelength++;                  /*to also copy the '\0' at the end of the string*/

    for (j = 0; j < (Linelength - i + 1); j++) /*shorten the main string*/
    {
        LinePointer[j] = LinePointer[j + i];
    }

    free(Myfloat);
    return result;
}

/*this functions checks if there is a float parameter at the start of the given string*/
int checkFloatParam(char *LinePointer)
{
    char current;
    int dotcounter = 0, isFloat = 1;
    int i = 0, flag = 1, numpredot = 0, numpostdot = 0;
    if (isWhiteChar(LinePointer[i])) /*skip white chars*/
        i = 1;

    if (LinePointer[i] == plusChar || LinePointer[i] == minusChar) /*if found + or - sign then all is good*/
        i++;

    while (flag)
    {
        current = LinePointer[i];
        if (isWhiteChar(current) || current == commaChar || current == newLineChar || current == EOF) /*if hit end of float*/
            flag = 0;

        if (current == dotChar) /*count periods*/
            dotcounter++;

        if (dotcounter > 1) /*more then one period is not float*/
            isFloat = 0;

        if (isdigit(current)) /*check numbers before and after period*/
            (dotcounter) ? numpostdot = 1 : (numpredot = 1);

        if (!(isdigit(current) || current == dotChar || isWhiteChar(current) || current == newLineChar || current == EOF || current == commaChar)) /*if hit weird char then not a float*/
            isFloat = 0;

        if (!isFloat)
            flag = 0;
        i++;
    }
    /*if there is a decimal point then check to see if there text on both sides, also check if there is
    more the 1 point and check for numbers appearing at all*/
    if ((dotcounter > 0 && (numpredot == 0 || numpostdot == 0)) || numpredot == 0 || dotcounter > 1)
        isFloat = 0;
    return isFloat;
}

/*this function checks if there is a 'A-Z' comp number char at the start of the given string
and if there is one it returns it and removes it from the string.
if there isnt one then it returns 0.*/
char extractCompParam(char *LinePointer)
{
    char current, result = 0;
    int i = 0, j, Linelength;

    current = LinePointer[i];
    while (isWhiteChar(current)) /*skip white chars*/
    {
        i++;
        current = LinePointer[i];
    }

    if (current >= 'A' && current <= 'F')
    {
        i++;
        if (isspace(LinePointer[i]) || LinePointer[i] == EOF || LinePointer[i] == commaChar) /*overwrite string with the bit after the complex number*/
        {
            result = current;
            Linelength = strlen(LinePointer);
            Linelength++; /*copy the \0 in the end also*/
            for (j = 0; j < (Linelength - i + 1); j++)
            {
                LinePointer[j] = LinePointer[j + i];
            }
        }
    }
    return result;
}

/*this function counts the consective commas in the start of the given string and returns it.*/
int countCommas(char *LinePointer)
{
    int i = 0, Commacounter = 0;
    while (LinePointer[i] == commaChar || isWhiteChar(LinePointer[i])) /*run through white chars and commas*/
    {
        if (LinePointer[i] == commaChar) /*count commas*/
            Commacounter++;
        i++;
    }
    return Commacounter;
}

/*This functions is only called after knowing there is a comma to be removed (countcommas()).
it removes 1 comma and also all white chars wrpping it(\n and EOF excluded)*/
void removeComma(char *LinePointer)
{
    int i = 0, j, LineLength;
    LineLength = strlen(LinePointer);
    while (isWhiteChar(LinePointer[i])) /*skip white chars before comma*/
    {
        i++;
    }
    i++;                                /*skip comma*/
    while (isWhiteChar(LinePointer[i])) /*skip white chars after comma*/
    {
        i++;
    }
    /*overwrite the string with the part after the comma */
    LineLength++; /*to copy the /0 in the end of string*/
    for (j = 0; j < (LineLength - i + 1); j++)
    {
        LinePointer[j] = LinePointer[j + i];
    }
}

/*this function looks for any kind of characters that are not white chars */
/*1 for no residual text, 0 for residual text*/
int checkResidualText(char *LinePointer)
{
    int i = 0, result = 1;
    while (LinePointer[i] != newLineChar && LinePointer[i] != EOF)
    {
        if (!isWhiteChar(LinePointer[i]))
            result = 0;
        i++;
    }
    return result;
}

/*this function checks if the string ends with EOF(return 1), or not (return 0)*/
int isLastEOF(char *LinePointer)
{
    int LineLength = 0;
    if (LinePointer == NULL)
    {
        return 0;
    }
    LineLength = strlen(LinePointer);
    if (LinePointer[LineLength - 1] == EOF)
        return 1;
    else
        return 0;
}

/*This function is like isspace but the new-line char doesnt count as a white character*/
int isWhiteChar(char c)
{
    if (c == ' ' || c == '\f' || c == '\t' || c == '\v' || c == '\r')
        return 1;
    else
        return 0;
}

/*this fuction return 1 if the line is all white characters, and 0 if not*/
int isOnlyWhiteChars(char *LinePointer)
{
    int i = 0, L = strlen(LinePointer), allwhitechars = 1;
    for (i = 0; i < L; i++) /*loop and check for white chars*/
    {
        if (!isspace(LinePointer[i]))
        {
            allwhitechars = 0;
        }
    }
    return allwhitechars;
}

/*this function checks if a line only containes white chars and EOF*/
int isOnlyEOF(char *LinePointer)
{
    int i = 0, L = strlen(LinePointer), onlyEOF = 1;
    for (i = 0; i < L - 1; i++)
    {
        if (!isspace(LinePointer[i]))
        {
            onlyEOF = 0;
        }
    }
    if (LinePointer[L - 1] != EOF)
    {
        onlyEOF = 0;
    }

    return onlyEOF;
}