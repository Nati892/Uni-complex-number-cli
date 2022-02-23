/*This program has 6 complex variales that the user can play with, the program uses the mycomp 
to make calcualtions on the complex variables.*/


#include "complex.h"
#include "mycomp.h"
int main()
{
	/*greetings message*/
	printf("Welcome!\nthis program has 6 complex variable that you can work with, you can set them, and do some fun math stuff!\n");
	printf("If your command follows the syntax rules, then the result will be printed out to you.\n");
	printf("When you want to quit then please use the 'stop' command.\n");
	printf("I hope you'll enjoy it!\n");
	initialize_numbers(myNumbers);
	GetInputLoop();

	return 0;
}

void GetInputLoop()
{
	int x = 1;
	char *Linepointer;

	while (x) /*input loop, gets line, parses it and then frees the space allocated to the line (if allocated at all)*/
	{
		Linepointer = getNewLine();
		printf("input:%s", Linepointer);
		handleLine(Linepointer);

		free(Linepointer);
	}
}
/*this function does all the input syntax validation and executes the command if the syntax is valid*/
void handleLine(char *LinePointer)
{
	int ThisCommand, continueCheck = 1, commacounter;
	float fParam1, fParam2;
	char compParam1, compParam2;
	if (isOnlyWhiteChars(LinePointer)) /*skip empty lines*/
	{
		return;
	}

	if (isOnlyEOF(LinePointer))
	{
		printf("You should have ended the program with the 'stop' command,\nBut the program will end anyway.\nbye bye");
		stop();
	}

	ThisCommand = extractCommand(LinePointer);
	/****** extracting parameters for differnet functions and executing them ******/

	if (ThisCommand == UNRECOGNIZED) /*Check command if recognized*/
	{
		printf("Undefined command name\n");
		continueCheck = 0;
	}

	if (ThisCommand != STOP && continueCheck) /*get first param for all commands except comp is a complex_number*/
	{
		if (countCommas(LinePointer)) /*check for immediate comma after command name*/
		{
			printf("Illegal comma\n");
			continueCheck = 0;
		}

		if (continueCheck && !isWhiteChar(LinePointer[0]) && LinePointer[0] != newLineChar && LinePointer[0] != EOF) /*make sure there is white char between the command and the text after*/
		{
			continueCheck = 0;
			printf("Undefined command name\n");
		}

		if ((checkResidualText(LinePointer)) && continueCheck) /*check that there is more text after the command name*/
		{
			continueCheck = 0;
			printf("Missing parameter!\n");
		}
		if (continueCheck)
		{

			compParam1 = extractCompParam(LinePointer); /*get first param for command*/
			if (compParam1 == BadInput)					/*check param to be good*/
			{
				printf("Undefined complex variable\n");
				continueCheck = 0;
			}
		}
	}

	if (continueCheck && (ThisCommand == ADD_COMP || ThisCommand == SUB_COMP || ThisCommand == MULT_COMP_COMP)) /*for second param as comp*/
	{
		commacounter = countCommas(LinePointer); /*comma handling*/
		if (commacounter == 0)
		{
			continueCheck = 0;
			if (checkResidualText(LinePointer))
			{
				printf("Missing parameter\n");
			}
			else
			{

				printf("Missing comma\n");
			}
		}
		else
		{
			if (commacounter > 1)
			{
				printf("Multiple consecutive commas\n");
				continueCheck = 0;
			}
		}
		if (continueCheck)
		{
			removeComma(LinePointer);
			if (checkResidualText(LinePointer)) /*check for second param*/
			{
				printf("Missing parameter\n");
				continueCheck = 0;
			}
		}
		if (continueCheck) /*get second complex param and handle it*/
		{
			compParam2 = extractCompParam(LinePointer);
			if (compParam2 == UNRECOGNIZED)
			{
				printf("Undefined complex variable\n");
				continueCheck = 0;
			}
		}
	}
	if (continueCheck && (ThisCommand == READ_COMP || ThisCommand == MULT_COMP_REAL || ThisCommand == MULT_COMP_IMG)) /*for second param as float*/
	{
		commacounter = countCommas(LinePointer); /*comma handling*/
		if (commacounter == 0)
		{
			continueCheck = 0;
			if (checkResidualText(LinePointer))
			{
				printf("Missing parameter\n");
			}
			else
			{

				printf("Missing comma\n");
			}
		}
		if (continueCheck)
		{
			removeComma(LinePointer);
			if (checkResidualText(LinePointer)) /*check for second param*/
			{
				printf("Missing parameter\n");
				continueCheck = 0;
			}
		}

		if (continueCheck && !checkFloatParam(LinePointer)) /*check for text to be a number*/
		{
			printf("Invalid parameter - not a number\n");
			continueCheck = 0;
		}
		if (continueCheck) /*get float number*/
		{
			fParam1 = extractFloatParam(LinePointer);
		}
	}

	if (continueCheck && ThisCommand == READ_COMP) /*check and get third param as float for read_comp only*/
	{
		commacounter = countCommas(LinePointer); /*comma handling*/
		if (commacounter == 0)
		{
			continueCheck = 0;
			if (checkResidualText(LinePointer))
			{
				printf("Missing parameter\n");
			}
			else
			{

				printf("Missing comma\n");
			}
		}
		if (continueCheck)
		{
			removeComma(LinePointer);
			if (checkResidualText(LinePointer)) /*check for second param*/
			{
				printf("Missing parameter\n");
				continueCheck = 0;
			}
		}

		if (continueCheck && !checkFloatParam(LinePointer)) /*check for text to be a number*/
		{
			printf("Invalid parameter - not a number\n");
			continueCheck = 0;
		}
		if (continueCheck) /*get float number*/
		{
			fParam2 = extractFloatParam(LinePointer);
		}
	}

	/*At this point the program already extracted all the data from the current line.
		now its just a final check good for all of them*/
	if (continueCheck)
	{
		if (!checkResidualText(LinePointer))
		{
			printf("Extraneous text after end of command\n");
			continueCheck = 0;
		}
	}

	/*exection stage - if the command is valid then now its time to execute it*/
	if (continueCheck)
	{
		switch (ThisCommand)
		{
		case READ_COMP:
			read_comp(&myNumbers[charToComplexindex(compParam1)], fParam1, fParam2);
			break;
		case ADD_COMP:
			add_comp(&myNumbers[charToComplexindex(compParam1)], &myNumbers[charToComplexindex(compParam2)]);
			break;
		case SUB_COMP:
			sub_comp(&myNumbers[charToComplexindex(compParam1)], &myNumbers[charToComplexindex(compParam2)]);
			break;
		case MULT_COMP_REAL:
			mult_comp_real(&myNumbers[charToComplexindex(compParam1)], fParam1);
			break;
		case MULT_COMP_IMG:
			mult_comp_img(&myNumbers[charToComplexindex(compParam1)], fParam1);
			break;
		case MULT_COMP_COMP:
			mult_comp_comp(&myNumbers[charToComplexindex(compParam1)], &myNumbers[charToComplexindex(compParam2)]);
			break;
		case PRINT_COMP:
			print_comp(&myNumbers[charToComplexindex(compParam1)]);
			break;
		case ABS_COMP:
			abs_comp(&myNumbers[charToComplexindex(compParam1)]);
			break;
		case STOP:
			printf("Have a great day!\nGoodbye now\n");
			stop();
			break;
		}
	}

	if (isLastEOF(LinePointer) && ThisCommand != STOP)
	{
		printf("You should have ended the program with the 'stop' command,\nBut the program will end anyway.\nbye bye");
		stop();
	}
}

/*returnes an enum val for command type and removes it from currently handled line if its a valid command*/
int handlecommandname(char *LinePointer, char *Thiscommand)
{
	int i, whiteChars = 0, commandlength, lineLength, result = 1;
	while (isWhiteChar(LinePointer[whiteChars]))
	{
		whiteChars++;
	}
	commandlength = strlen(Thiscommand) + whiteChars;
	result = SearchCommand(Thiscommand);
	lineLength = strlen(LinePointer); /*remove command name from line String*/

	for (i = 0; i < (lineLength - commandlength + 1); i++) /*remove the command string at the start*/
		LinePointer[i] = LinePointer[i + commandlength];
	return result;
}

/*Extract the command from the current line, and return it as an enum*/
int extractCommand(char *LinePointer)
{
	int i = 0, result;
	int commandLength = 0;
	char *thiscommand;
	while (isWhiteChar(LinePointer[i])) /*skip white chars before command name*/
	{
		i++;
	}

	thiscommand = (char *)malloc(0);
	while (LinePointer[i] == underScoreChar || islower(LinePointer[i]))
	{
		commandLength++;
		thiscommand = realloc(thiscommand, commandLength);
		thiscommand[commandLength - 1] = LinePointer[i];
		i++;
	}

	commandLength++;
	thiscommand = realloc(thiscommand, commandLength);
	thiscommand[commandLength - 1] = 0;
	result = handlecommandname(LinePointer, thiscommand);
	free(thiscommand);
	return result;
}

/*returns the type of command as an enum value*/
int SearchCommand(char *thiscommand)
{
	int result = UNRECOGNIZED;
	if (!strcmp(thiscommand, "read_comp"))
		result = READ_COMP;
	if (!strcmp(thiscommand, "print_comp"))
		result = PRINT_COMP;
	if (!strcmp(thiscommand, "add_comp"))
		result = ADD_COMP;
	if (!strcmp(thiscommand, "sub_comp"))
		result = SUB_COMP;
	if (!strcmp(thiscommand, "mult_comp_real"))
		result = MULT_COMP_REAL;
	if (!strcmp(thiscommand, "mult_comp_img"))
		result = MULT_COMP_IMG;
	if (!strcmp(thiscommand, "mult_comp_comp"))
		result = MULT_COMP_COMP;
	if (!strcmp(thiscommand, "abs_comp"))
		result = ABS_COMP;
	if (!strcmp(thiscommand, "stop"))
		result = STOP;
	return result;
}

/*returns a pointer to a string holding the current command*/
char *getNewLine()
{
	char *NewLine;
	char inChar;
	int LineLength = 0;
	printf("Please enter a new command\n");
	NewLine = (char *)malloc(LineLength);
/*builds a variable size String holding the current line, using dynamic allocation*/
	while (inChar != '\n' && inChar != EOF) 
	{
		inChar = getchar();
		LineLength++;
		NewLine = realloc(NewLine, LineLength);
		NewLine[LineLength - 1] = inChar;
	}
	/*add a \0 in the end of string*/
	LineLength++;
	NewLine = realloc(NewLine, LineLength);
	NewLine[LineLength - 1] = '\0';
	return NewLine;
}

/*gets a char representing a complex variable and returns its location in the complex numbers array*/
int charToComplexindex(char compchar)
{
	int i, result;
/*searchs by name*/
	for (i = 0; i < numberOfComplexVariables; i++)
	{
		if (myNumbers[i].Name == compchar)
		{
			result = i;
		}
	}
	return result;
}

/*Initializer for the A-F complex vars to 0+0i*/
void initialize_numbers(complex *myNumbers)
{
	int i;
	for (i = 0; i < numberOfComplexVariables; i++)
	{
		myNumbers[i].Name = ('A' + i);
		myNumbers[i].R = 0.0;
		myNumbers[i].I = 0.0;
	}
}
