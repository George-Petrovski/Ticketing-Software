// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : George Petrovski
//  Student ID    : 148853203
//  Student Email : gpetrovski1@myseneca.ca
//  Course Section: NNN
// ===================================================================================

#ifndef TICKET_H_
#define TICKET_H_

//#include "accountTicketingUI.h"

typedef struct Message
{
	char account_type;
	char name[31];
	char msg_details[151];
}MESSAGE;

typedef struct Ticket
{
	int tick_num;
	int cust_acc_num;
	int status : 1;
	char subj_line[31];
	int counter;
	MESSAGE messages[20];
}TICKET;

int loadTickets(TICKET*, int);
int saveTickets(TICKET*, int);
int archClosedTickets(TICKET*, const int);
void archTicketsStats();

void newTicket(TICKET*, int, const char*);

void modTickSubject(TICKET*);
void addTickMessage(TICKET*, const char*, char);
void closeTick(TICKET*, const char*, char);
void openTick(TICKET*);

#endif // !TICKET_H_