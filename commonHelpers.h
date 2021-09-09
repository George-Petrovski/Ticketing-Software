// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : George Petrovski
//  Student ID    : 148853203
//  Student Email : gpetrovski1@myseneca.ca
//  Course Section: NNN
// ===================================================================================

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
#define _CRT_SECURE_NO_WARNINGS

//#include "accountTicketingUI.h"

int currentYear(void);
void clearStandardInputBuffer(void);

int getInteger();
int getPositiveInteger();
int getPositiveIntegerWithZero();
int getIntFromRange(int min, int max);

double getDouble();
double getPositiveDouble();

char getCharOption(char qwerty[7]);
void getCString(char* cstr, int min, int max);



#endif // !COMMON_HELPERS_H_



