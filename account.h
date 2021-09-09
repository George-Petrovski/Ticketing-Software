// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : George Petrovski
//  Student ID    : 148853203
//  Student Email : gpetrovski1@myseneca.ca
//  Course Section: NNN
// ===================================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct UserLogin
{
	char name[31];
	char login_name[11];
	char password[9];
}USERLOGIN;

typedef struct Demographic
{
	int birth_year;
	double h_income;
	char country[31];
}DEMOGRAPHIC;

typedef struct Account
{
	int account_num;
	char account_type;
	USERLOGIN login;
	DEMOGRAPHIC demographic;
}ACCOUNT;

int loadAccounts(ACCOUNT* , int);
int saveAccounts(ACCOUNT* , int);
void archAccountsStats();

void getAccount(ACCOUNT*, int new_acc_num);
void getUserLogin(USERLOGIN*);
void getDemographic(DEMOGRAPHIC*);

void updateAccount(ACCOUNT*);
void updateUserLogin(USERLOGIN*);
void updateDemographic(DEMOGRAPHIC*);

#endif // !ACCOUNT_H_