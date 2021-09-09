// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : George Petrovski
//  Student ID    : 148853203
//  Student Email : gpetrovski1@myseneca.ca
//  Course Section: NNN
// ===================================================================================

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "ticket.h"
#include "account.h"
#include "commonHelpers.h"

typedef struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
}ACCOUNTTICKETINGDATA;

void archAccount(ACCOUNT*, TICKET*, const int);

void displayAccountSummaryHeader(void);
void displayAccountSummaryRecord(const ACCOUNT*);

void displayAccountDetailHeader(void);
void displayAccount(const ACCOUNT*);

void applicationStartup(ACCOUNTTICKETINGDATA*);
int menuLogin(ACCOUNTTICKETINGDATA data[]);
void menuAgent(ACCOUNTTICKETINGDATA* , const ACCOUNT* );
void menuCustomer(TICKET*, int, const ACCOUNT*);
int findAccountIndexByAcctNum(int, const ACCOUNT*, int, int);
int findTicketIndexByTickNum(int, const TICKET*, int);
void displayAllAccountSummaryRecords(const ACCOUNT*, int);
void displayAllAccountDetailRecords(const ACCOUNT*, int);

void agentDisplayTicketHeader();
void displayTicketMessages(const TICKET* );
void displayMessage(const MESSAGE* );

void agentDisplayMenu();
void customerDisplayMenu();

void agentAddAccount(ACCOUNTTICKETINGDATA*);
void agentModifyExistingAccount(ACCOUNTTICKETINGDATA*);
void agentRemoveAccount(ACCOUNTTICKETINGDATA*, const ACCOUNT*);
void agentListNewTickets(ACCOUNTTICKETINGDATA*);
void agentListActiveTickets(ACCOUNTTICKETINGDATA*);
void agentListClosedTickets(ACCOUNTTICKETINGDATA*);
void agentModifyTicket(ACCOUNTTICKETINGDATA*, const ACCOUNT*);
void agentArchTicketOption(ACCOUNTTICKETINGDATA*);

int displaySelectedTicketMessages(const ACCOUNTTICKETINGDATA*);
void agentDisplayTicket(const int, const ACCOUNTTICKETINGDATA*);
int accountVerification(int*, ACCOUNTTICKETINGDATA*);

void customerNewTicket(TICKET*, const int, const ACCOUNT*);
void customerModifyActiveTicket(TICKET*, const int, const ACCOUNT*);
void customerListTickets(TICKET*, const int, const ACCOUNT*);

// Pause execution until user enters the enter key
void pauseExecution(void);

#endif // !ACCOUNT_TICKETING_UI_H_
