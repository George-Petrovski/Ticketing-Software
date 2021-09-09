// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : George Petrovski
//  Student ID    : 148853203
//  Student Email : gpetrovski1@myseneca.ca
//  Course Section: NNN
// ===================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>

#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

// As demonstrated in the course notes:
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int getInteger()
{
	int error;
	int x = 0;
	char newLine = '0';

	do
	{
		error = 0;
		scanf("%d%c", &x, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			error = 1;
			printf("ERROR: Value must be an integer: ");
		}

	} while (error == 1);
	return x;
}

int getPositiveInteger()
{
	int x = 0;
	do
	{
		x = getInteger();
		if (x <= 0)
		{
			
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (x <= 0);
	return x;
}

int getPositiveIntegerWithZero()
{
	int x = 0;
	do
	{
		x = getInteger();
		if (x < 0)
		{

			printf("ERROR: Value must be positive or zero: ");
		}
	} while (x < 0);
	return x;
}

int getIntFromRange(int min, int max)
{
	int x = 0;
	do
	{
		x = getInteger();
		if (x < min || x > max)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", min, max);
		}
	} while (x < min || x > max);
	return x;
}

double getDouble()
{
	double x = 0;
	int error;
	char newLine = '0';

	do
	{
		error = 0;
		scanf("%lf%c", &x, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			error = 1;
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (error == 1);
	return x;
}

double getPositiveDouble()
{
	double x = 0;
	do
	{
		x = getDouble();
		if (x <= 0)
		{

			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (x <= 0);
	return x;
}

char getCharOption(char qwerty[7])
{
	char x = 'z';
	int i;

	int error;
	char newLine = '0';

	do
	{
		error = 0;
		scanf("%c%c", &x, &newLine);
		if (newLine != '\n')
		{
			clearStandardInputBuffer();
			error = 1;
			printf("ERROR: Character must be one of [%s]: ", qwerty);
		}
		else
		{
			for (i = 0; i < 6 && x != qwerty[i]; i++)
			{
				if (x != qwerty[i])
				{
					error = 1;
				}
			}
			if (x == qwerty[i])
			{
				error = 0;
			}
			else
			{
				printf("ERROR: Character must be one of [%s]: ", qwerty);
			}
		}

	} while (error == 1);
	return x;
}

void getCString(char* cstr, int min, int max)
{
	int i;
	int count;
	int error;

	do
	{
		error = 0;
		count = 0;
		char x[151] = { '\0' };
		scanf("%150[^\n]", x);
		for (i = 0; i < 152 && x[i] != '\0'; i++)
		{
			if (x[i] != '\0')
			{
				count++;
			}
		}

		if (count > max || count < min)
		{
			error = 1;
			if (min == max)
			{
				printf("ERROR: String length must be exactly %d chars: ", min);
			}
			else if (count > max)
			{
				printf("ERROR: String length must be no more than %d chars: ", max);
			}
			else
			{
				printf("ERROR: String length must be between %d and %d chars: ", min, max);
			}
		}
		
		if (count <= max && count >= min)
		{
			for (i = 0; i < count + 1; i++)
			{
				if (i < count)
				{
					cstr[i] = x[i];
				}
				else
				{
					cstr[i] = '\0';
				}
			}
		}
		clearStandardInputBuffer();
	} while (error == 1);

}

