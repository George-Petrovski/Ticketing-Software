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
#include <string.h>
#include <ctype.h>

#include "accountTicketingUI.h"

int loadAccounts(ACCOUNT* accounts, int size)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp) && i < size)
		{
			fscanf(fp, "%d%*c%c%*c%[^~]%*c%[^~]%*c%[^~]%*c%d%*c%lf%*c%[^\n]",
				&accounts[i].account_num,
				&accounts[i].account_type,
				accounts[i].login.name,
				accounts[i].login.login_name,
				accounts[i].login.password,
				&accounts[i].demographic.birth_year,
				&accounts[i].demographic.h_income,
				accounts[i].demographic.country);
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return i;
}


int saveAccounts(ACCOUNT* accounts, int size)
{
	int accounts_saved = 0, i = 0;
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "w");
	if (fp != NULL)
	{
		while (i < size)
		{
			if (accounts[i].account_num > 0)
			{
				accounts_saved++;
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
					accounts[i].account_num,
					accounts[i].account_type,
					accounts[i].login.name,
					accounts[i].login.login_name,
					accounts[i].login.password,
					accounts[i].demographic.birth_year,
					accounts[i].demographic.h_income,
					accounts[i].demographic.country);
			}
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return accounts_saved;
}

void archAccountsStats()
{
	ACCOUNT archAcc[100] = { {0} };
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("accounts_arc.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d%*c%c%*c%[^~]%*c%[^~]%*c%[^~]%*c%d%*c%lf%*c%[^\n]",
				&archAcc[i].account_num,
				&archAcc[i].account_type,
				archAcc[i].login.name,
				archAcc[i].login.login_name,
				archAcc[i].login.password,
				&archAcc[i].demographic.birth_year,
				&archAcc[i].demographic.h_income,
				archAcc[i].demographic.country);
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	--i;
	printf("There are %d account(s) currently archived.\n\n", i);
}

void getAccount(ACCOUNT* acc, int new_acc_num)
{
	acc->account_num = new_acc_num;
	printf("New Account Data (Account#:%d)\n", new_acc_num);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	acc->account_type = getCharOption("AC");
	printf("\n");
}

void getUserLogin(USERLOGIN* login)
{
	int i, loop;
	int count_digit, count_uppercase, count_lowercase, count_symbol;
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	
	do
	{
		loop = 0; 
		printf("Enter user login (10 chars max): ");
		getCString(login->login_name, 1, 10);
		for (i = 0; i != strlen(login->login_name); i++)
		{
			if (isspace(login->login_name[i]))
			{
				loop = 1;
				i = strlen(login->login_name) - 1;
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			}
		}
	} while (loop == 1);
	
	printf("Enter the display name (30 chars max): ");
	getCString(login->name, 1, 30);

	do
	{
		loop = 0;
		count_digit = 0;
		count_uppercase = 0;
		count_lowercase = 0;
		count_symbol = 0;
		printf("Enter the password (must be 8 chars in length): ");
		getCString(login->password, 8, 8);
		for (i = 0; i != strlen(login->password); i++)
		{
			if (isdigit(login->password[i]))
			{
				count_digit += 1;
			}
			if (isupper(login->password[i]))
			{
				count_uppercase += 1;
			}
			if (islower(login->password[i]))
			{
				count_lowercase += 1;
			}
			if (login->password[i] == '!' || login->password[i] == '@' || login->password[i] == '#' || 
				login->password[i] == '$' || login->password[i] == '%' || login->password[i] == '^' || 
				login->password[i] == '&' || login->password[i] == '*')
			{
				count_symbol += 1;
			}
		}
		if (count_digit != 2 || count_uppercase != 2 || count_lowercase != 2 || count_symbol != 2)
		{
			loop = 1;
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}
	} while (loop == 1);
	printf("\n");
}

void getDemographic(DEMOGRAPHIC* demographic)
{
	int i;
	char temp_country[31];
	int min_year, max_year;
	min_year = currentYear() - 110;
	max_year = currentYear() - 18;
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	demographic->birth_year = getIntFromRange(min_year, max_year);
	printf("Enter the household Income: $");
	demographic->h_income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(demographic->country, 2, 30);
	
	for (i = 0; i != strlen(demographic->country); i++)
	{
		temp_country[i] = demographic->country[i];
		demographic->country[i] = toupper(temp_country[i]);
	}
	printf("\n");

}

void updateAccount(ACCOUNT* accounts)
{
	printf("Enter the account type (A=Agent | C=Customer): ");
	accounts->account_type = getCharOption("AC");
	//printf("\n");
}

void updateUserLogin(USERLOGIN* login)
{
	int select;
	int i, loop;
	int count_digit, count_uppercase, count_lowercase, count_symbol;
	do
	{
		printf("User Login: %s - Update Options\n", login->login_name);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", login->name);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);
		printf("\n");
		switch (select)
		{
		case 1:
			printf("Enter the display name (30 chars max): ");
			getCString(login->name, 1, 30);
			printf("\n");
			break;
		case 2:
			do
			{
				loop = 0;
				count_digit = 0;
				count_uppercase = 0;
				count_lowercase = 0;
				count_symbol = 0;
				printf("Enter the password (must be 8 chars in length): ");
				getCString(login->password, 8, 8);
				for (i = 0; i != strlen(login->password); i++)
				{
					if (isdigit(login->password[i]))
					{
						count_digit += 1;
					}
					if (isupper(login->password[i]))
					{
						count_uppercase += 1;
					}
					if (islower(login->password[i]))
					{
						count_lowercase += 1;
					}
					if (login->password[i] == '!' || login->password[i] == '@' || login->password[i] == '#' ||
						login->password[i] == '$' || login->password[i] == '%' || login->password[i] == '^' ||
						login->password[i] == '&' || login->password[i] == '*')
					{
						count_symbol += 1;
					}
				}
				if (count_digit != 2 || count_uppercase != 2 || count_lowercase != 2 || count_symbol != 2)
				{
					loop = 1;
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*\n");
				}
			} while (loop == 1);
			printf("\n");
			break;
		}
	} while (select != 0);

}

void updateDemographic(DEMOGRAPHIC* demographic)
{
	int select;
	int i;
	char temp_country[31];
	do
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demographic->h_income);
		printf("2) Country (current value: %s)\n", demographic->country);
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);
		printf("\n");
		switch (select)
		{
		case 1:
			printf("Enter the household Income: $");
			demographic->h_income = getPositiveDouble();
			printf("\n");
			break;
		case 2:
			printf("Enter the country (30 chars max.): ");
			getCString(demographic->country, 2, 30);
			for (i = 0; i != strlen(demographic->country); i++)
			{
				temp_country[i] = demographic->country[i];
				demographic->country[i] = toupper(temp_country[i]);
			}
			printf("\n");
			break;
		}
	} while (select != 0);
}