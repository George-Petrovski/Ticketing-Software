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

#include "accountTicketingUI.h"

void archAccount(ACCOUNT* accounts, TICKET* tickets, const int TickArrSize)
{
	FILE* fp = NULL;
	fp = fopen("accounts_arc.txt", "a");
	if (fp != NULL)
	{
		fprintf(fp, "%5d~%c~%s~%s~%s~%4d~%.2lf~%s\n",
			accounts->account_num,
			accounts->account_type,
			accounts->login.name,
			accounts->login.login_name,
			accounts->login.password,
			accounts->demographic.birth_year,
			accounts->demographic.h_income,
			accounts->demographic.country);
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}

	int j, i = 0;
	fp = fopen("tickets_arc.txt", "a");
	if (fp != NULL)
	{

		while (i < TickArrSize)
		{
			if (tickets[i].tick_num > 0 && tickets[i].cust_acc_num == accounts->account_num)
			{
				if (!tickets[i].status)
				{
					fprintf(fp, "%d|%d|%d|%s|%d|",
						tickets[i].tick_num,
						tickets[i].cust_acc_num,
						tickets[i].status,
						tickets[i].subj_line,
						tickets[i].counter);

					j = 0;
					while (j < (tickets[i].counter))
					{
						fprintf(fp, "%c|%s|%s|",
							tickets[i].messages[j].account_type,
							tickets[i].messages[j].name,
							tickets[i].messages[j].msg_details);
						j++;
					}
					fprintf(fp, "\n");
				}
				tickets[i].tick_num = 0;
			}
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
}

void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountSummaryRecord(const ACCOUNT* account)
{
	char customer[9] = "CUSTOMER";
	char agent[9] = "AGENT";
	printf("%05d ", account->account_num);
	if (account->account_type == 'C')
	{
		printf("%-9s ", customer);
	}
	if (account->account_type == 'A')
	{
		printf("%-9s ", agent);
	}
	printf("%5d\n", account->demographic.birth_year);
}


void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccount(const ACCOUNT* account)
{
	// Display the respective data to align to the table header above:
	char customer[9] = "CUSTOMER";
	char agent[9] = "AGENT";
	int i;
	printf("%05d ", account->account_num);
	if (account->account_type == 'C')
	{
		printf("%-9s ", customer);
	}
	if (account->account_type == 'A')
	{
		printf("%-9s ", agent);
	}
	printf("%5d $%10.2lf %-10s %-15s %-10s ", account->demographic.birth_year, account->demographic.h_income,
		account->demographic.country, account->login.name, account->login.login_name);

	for (i = 2; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			printf("%c", account->login.password[i - 2]);
		}
		else
		{
			printf("*");
		}
	}
	putchar('\n');
}

void applicationStartup(ACCOUNTTICKETINGDATA* data)
{
	int acc_selection;

	do
	{
		acc_selection = menuLogin(data);
		if (data->accounts[acc_selection].account_type == 'C')
		{
			menuCustomer(data->tickets, data->TICKET_MAX_SIZE, &data->accounts[acc_selection]);
		}
		else if (data->accounts[acc_selection].account_type == 'A')
		{
			menuAgent(data, &data->accounts[acc_selection]);
		}
	} while (acc_selection != -1);
	
	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");

}

int menuLogin(ACCOUNTTICKETINGDATA data[])
{
	int selection;
	char exit;
	int loop;

	do
	{
		loop = 0;

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 1);
		printf("\n");
		if (!selection)
		{
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			exit = getCharOption("yYnN");
			printf("\n");
			switch (exit)
			{
			case 'n' :
			case 'N' :
				loop = 1;
				break;
			case 'y' :
			case 'Y' :
				selection = -1;
				break;
			}
		}
		if (selection == 1)
		{
			//account verification code
			loop = accountVerification(&selection, data);
		}
	} while (loop);
	return selection;
}

void menuAgent(ACCOUNTTICKETINGDATA* data, const ACCOUNT* current_acc)
{
	int selection, numSavedTicks, numSavedAcc;
	do
	{
		printf("AGENT: %s (%d)\n", current_acc->login.name, current_acc->account_num);
		agentDisplayMenu();
		selection = getIntFromRange(0, 12);
		printf("\n");
		switch (selection)
		{
		case 1:
			agentAddAccount(data);
			break;
		case 2:
			agentModifyExistingAccount(data);
			break;
		case 3:
			agentRemoveAccount(data, current_acc);
			break;
		case 4:
			displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;
		case 5:
			displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;
		case 6:
			//this will display tickets with only 1 message in them
			agentListNewTickets(data);
			break;
		case 7:
			//this will display the active tickets
			agentListActiveTickets(data);
			break;
		case 8:
			//this will display the closed tickets
			agentListClosedTickets(data);
			break;
		case 9:
			//agent ticket modification code
			agentModifyTicket(data, current_acc);
			break;
		case 10:
			//option to archive all tickets with the status closed
			agentArchTicketOption(data);
			break;
		case 11:
			//display stats for all archived accounts
			archAccountsStats();
			pauseExecution();
			break;
		case 12:
			//display stats for all archived tickets
			archTicketsStats();
			pauseExecution();
			break;
		}
	} while (selection != 0);

	numSavedAcc = saveAccounts(data->accounts, data->ACCOUNT_MAX_SIZE);
	numSavedTicks = saveTickets(data->tickets, data->TICKET_MAX_SIZE);

	printf("Saving session modifications...\n");
	printf("   %d account saved.\n", numSavedAcc);
	printf("   %d tickets saved.\n", numSavedTicks);
	printf("### LOGGED OUT ###\n\n");
}

void menuCustomer(TICKET* tickets, int arrSize, const ACCOUNT* data_current_acc)
{
	int selection, savedTicks;
	do
	{
		printf("CUSTOMER: %s (%d)\n", data_current_acc->login.name, data_current_acc->account_num);
		customerDisplayMenu();
		selection = getIntFromRange(0, 4);
		printf("\n");
		switch (selection)
		{
		case 1:
			displayAccountDetailHeader();
			displayAccount(data_current_acc);
			printf("\n");
			pauseExecution();
			break;
		case 2:
			customerNewTicket(tickets, arrSize, data_current_acc);
			break;
		case 3:
			customerModifyActiveTicket(tickets, arrSize, data_current_acc);
			break;
		case 4:
			customerListTickets(tickets, arrSize, data_current_acc);
			break;
		}
	} while (selection != 0);

	savedTicks = saveTickets(tickets, arrSize);

	printf("Saving session modifications...\n");
	printf("   %d tickets saved.\n", savedTicks);
	printf("### LOGGED OUT ###\n\n");
}

int findAccountIndexByAcctNum(int acc_num, const ACCOUNT* accounts, int AccountsArrSize, int zero_or_not)
{

	int i, found = 0;
	if (zero_or_not == 0)
	{
		for (i = 0; i < AccountsArrSize && !found; i++)
		{
			if (acc_num == accounts[i].account_num)
			{
				found = 1;
				i--;
			}
		}
	}
	else
	{
		printf("Enter the account#: ");
		acc_num = getPositiveInteger();
		for (i = 0; i < AccountsArrSize && !found; i++)
		{
			if (acc_num == accounts[i].account_num)
			{
				found = 1;
				i--;
			}
		}
	}

	if (!found)
	{
		i = -1;
	}
	return i;
}

int findTicketIndexByTickNum(int tick_num, const TICKET* tickets, int TickArrSize)
{
	int i, found = 0;
	for (i = 0; i < TickArrSize && !found; i++)
	{
		if (tick_num == tickets[i].tick_num)
		{
			found = 1;
			i--;
		}
	}
	if (!found)
	{
		i = -1;
	}
	return i;
}

void displayAllAccountSummaryRecords(const ACCOUNT* accounts, int AccountArrSize)
{
	int i;
	displayAccountSummaryHeader();
	for (i = 0; i < AccountArrSize; i++)
	{
		if ((accounts+i)->account_num != 0)
		{
			displayAccountSummaryRecord(accounts + i);
		}
	}
	printf("\n");
}

void displayAllAccountDetailRecords(const ACCOUNT* accounts, int AccountArrSize)
{
	int i;
	displayAccountDetailHeader();
	for (i = 0; i < AccountArrSize; i++)
	{
		if (accounts[i].account_num != 0)
		{
			displayAccount(&accounts[i]);
		}
	}
	printf("\n");
}

void agentDisplayTicketHeader()
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void agentDisplayMenu()
{
	printf("==============================================\n");
	printf("Account Ticketing System - Agent Menu\n");
	printf("==============================================\n");
	printf(" 1) Add a new account\n");
	printf(" 2) Modify an existing account\n");
	printf(" 3) Remove an account\n");
	printf(" 4) List accounts: summary view\n");
	printf(" 5) List accounts: detailed view\n");
	printf("----------------------------------------------\n");
	printf(" 6) List new tickets\n");
	printf(" 7) List active tickets\n");
	printf(" 8) List closed tickets\n");
	printf(" 9) Manage a ticket\n");
	printf("10) Archive closed tickets\n");
	printf("----------------------------------------------\n");
	printf("11) View archived account statistics\n");
	printf("12) View archived tickets statistics\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n\n");
	printf("Selection: ");
}

void customerDisplayMenu()
{
	printf("==============================================\n");
	printf("Customer Main Menu\n");
	printf("==============================================\n");
	printf("1) View your account detail\n");
	printf("2) Create a new ticket\n");
	printf("3) Modify an active ticket\n");
	printf("4) List my tickets\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n\n");
	printf("Selection: ");
}

void displayTicketMessages(const TICKET* tickets)
{
	int i;
	printf("================================================================================\n");
	printf("%06d ", tickets->tick_num);
	if (tickets->status)
	{
		printf("(ACTIVE) ");
	}
	else
	{
		printf("(CLOSED) ");
	}
	printf("Re: %s\n", tickets->subj_line);
	printf("================================================================================\n");

	for (i = 0; i < 20; i++)
	{
		if (tickets->messages[i].account_type == 'A' || tickets->messages[i].account_type == 'C')
		{
				displayMessage(&tickets->messages[i]);
				if ((i + 1) % 5 == 0 && tickets->counter != (i+1))
				{
					pauseExecution();
				}
		}
	}
	pauseExecution();
}
void displayMessage(const MESSAGE* messages)
{
	if (messages->account_type == 'A')
	{
		printf("AGENT (%s):\n", messages->name);
	}
	else if (messages->account_type == 'C')
	{
		printf("CUSTOMER (%s):\n", messages->name);
	}
	printf("   %s\n\n", messages->msg_details);
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

void agentAddAccount(ACCOUNTTICKETINGDATA* data)
{
	int i, empty_slot, count_acc, biggest_acc_num;
	for (i = 0; i < data->ACCOUNT_MAX_SIZE && data->accounts[i].account_num != 0; i++)
	{
		//if the slot is not empty, it will continue looping
		//if slot is empty, for loop will exit after increasing i by 1
	}
	empty_slot = i;
	count_acc = 1;
	//this code will figure out the next account number to generate
	biggest_acc_num = data->accounts[0].account_num;
	for (i = 1; i < data->ACCOUNT_MAX_SIZE; i++)
	{
		if (data->accounts[i].account_num > 0)
		{
			++count_acc;
		}
		if (biggest_acc_num < data->accounts[i].account_num)
		{
			biggest_acc_num = data->accounts[i].account_num;
		}
	}
	biggest_acc_num += 1;

	if (count_acc < data->ACCOUNT_MAX_SIZE)
	{
		getAccount(&data->accounts[empty_slot], biggest_acc_num);
		getUserLogin(&data->accounts[empty_slot].login);
		getDemographic(&data->accounts[empty_slot].demographic);
		printf("*** New account added! ***\n\n");
	}
	else
	{
		printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
	}

	pauseExecution();
}

void agentModifyExistingAccount(ACCOUNTTICKETINGDATA* data)
{
	int arrPlace, update;
	arrPlace = findAccountIndexByAcctNum(0, data->accounts, data->ACCOUNT_MAX_SIZE, 1);
	printf("\n");
	do
	{
		printf("Account: %d - Update Options\n", data->accounts[arrPlace].account_num);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", data->accounts[arrPlace].account_type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		update = getIntFromRange(0, 3);
		printf("\n");
		switch (update)
		{
		case 1:
			updateAccount(&data->accounts[arrPlace]);
			break;
		case 2:
			updateUserLogin(&data->accounts[arrPlace].login);
			break;
		case 3:
			updateDemographic(&data->accounts[arrPlace].demographic);
			break;
		}
	} while (update != 0);
}

void agentRemoveAccount(ACCOUNTTICKETINGDATA* data, const ACCOUNT* current_acc)
{
	int arrPlace;
	char remove;
	arrPlace = findAccountIndexByAcctNum(0, data->accounts, data->ACCOUNT_MAX_SIZE, 1);
	if (current_acc->account_num != data->accounts[arrPlace].account_num)
	{
		displayAccountDetailHeader();
		displayAccount(&data->accounts[arrPlace]);
		printf("\n");
		printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
		remove = getCharOption("YN");
		printf("\n");
		switch (remove)
		{
		case 'N':
			printf("*** No changes made! ***\n\n");
			pauseExecution();
			break;
		case 'Y':
			archAccount(&data->accounts[arrPlace], data->tickets, data->TICKET_MAX_SIZE);
			data->accounts[arrPlace].account_num = 0;
			printf("*** Account Removed! ***\n\n");
			pauseExecution();
			break;
		}
	}
	else if (current_acc->account_num == data->accounts[arrPlace].account_num)
	{
		printf("\nERROR: You can't remove your own account!\n\n");
		pauseExecution();
	}
	else
	{
		printf("\nERROR: No such account!\n\n");
		pauseExecution();
	}
}

void agentListNewTickets(ACCOUNTTICKETINGDATA* data)
{
	int i, tick_select;
	do
	{
		agentDisplayTicketHeader();
		//loop through all the tickets
		for (i = 0; i < data->TICKET_MAX_SIZE; ++i)
		{
			if (data->tickets[i].counter == 1 && data->tickets[i].tick_num > 0)
			{
				agentDisplayTicket(i, data);
			}
		}
		tick_select = displaySelectedTicketMessages(data);
	} while (tick_select > 0);
	printf("\n");
}

void agentListActiveTickets(ACCOUNTTICKETINGDATA* data)
{
	int i, tick_select;
	do
	{
		agentDisplayTicketHeader();
		//go through all the tickets
		for (i = 0; i < data->TICKET_MAX_SIZE; ++i)
		{
			if (data->tickets[i].status && data->tickets[i].tick_num > 0)
			{
				agentDisplayTicket(i, data);
			}
		}
		tick_select = displaySelectedTicketMessages(data);
	} while (tick_select > 0);
	printf("\n");
}

void agentListClosedTickets(ACCOUNTTICKETINGDATA* data)
{
	int i, tick_select;
	do
	{
		agentDisplayTicketHeader();
		//go through all the tickets
		for (i = 0; i < data->TICKET_MAX_SIZE; ++i)
		{
			//only prints out tickets that are active 
			if (!data->tickets[i].status && data->tickets[i].tick_num > 0)
			{
				agentDisplayTicket(i, data);
			}
		}
		tick_select = displaySelectedTicketMessages(data);
	} while (tick_select > 0);
	printf("\n");
}

void agentModifyTicket(ACCOUNTTICKETINGDATA* data, const ACCOUNT* current_acc)
{
	int tick_select, arrTick, select_mod;
	printf("Enter ticket number: ");
	tick_select = getPositiveInteger();

	arrTick = findTicketIndexByTickNum(tick_select, data->tickets, data->TICKET_MAX_SIZE);
	printf("\n");
	if (arrTick >= 0)
	{
		do
		{
			printf("----------------------------------------\n");
			printf("Ticket %06d - Update Options\n", data->tickets[arrTick].tick_num);
			printf("----------------------------------------\n");
			printf("Status  : ");
			if (data->tickets[arrTick].status)
			{
				printf("ACTIVE\n");
			}
			else
			{
				printf("CLOSED\n");
			}
			printf("Subject : %s\n", data->tickets[arrTick].subj_line);
			printf("Acct#   : %d\n", data->tickets[arrTick].cust_acc_num);
			printf("Customer: %s\n", data->tickets[arrTick].messages[0].name);
			printf("----------------------------------------\n");
			printf("1) Add a message\n");
			printf("2) Close ticket\n");
			printf("3) Re-open ticket\n");
			printf("0) Done\n");
			printf("Selection: ");
			select_mod = getIntFromRange(0, 3);
			printf("\n");
			switch (select_mod)
			{
			case 1:
				if (data->tickets[arrTick].status && data->tickets[arrTick].counter < 20)
				{
					addTickMessage(&data->tickets[arrTick], current_acc->login.name, current_acc->account_type);
				}
				else if (!data->tickets[arrTick].status)
				{
					printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
				}
				else
				{
					printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
				}
				break;
			case 2:
				if (data->tickets[arrTick].status)
				{
					closeTick(&data->tickets[arrTick], current_acc->login.name, 'A');
				}
				else
				{
					printf("ERROR: Ticket is already closed!\n\n");
				}
				break;
			case 3:
				if (!data->tickets[arrTick].status)
				{
					openTick(&data->tickets[arrTick]);
				}
				else
				{
					printf("ERROR: Ticket is already active!\n\n");
				}
				break;
			}
		} while (select_mod != 0);
	}
	else
	{
		printf("ERROR: Invalid ticket number.\n\n");
	}
}

void agentArchTicketOption(ACCOUNTTICKETINGDATA* data)
{
	char archTicks;
	int numTicksArched;
	printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
	archTicks = getCharOption("YN");
	if (archTicks == 'Y')
	{
		numTicksArched = archClosedTickets(data->tickets, data->TICKET_MAX_SIZE);
		printf("\n*** %d tickets archived ***\n\n", numTicksArched);
	}
	pauseExecution();
}

int displaySelectedTicketMessages(const ACCOUNTTICKETINGDATA* data)
{
	int tick_select, arrTick;
	printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
	printf("Enter the ticket number to view the messages or\n");
	printf("0 to return to previous menu: ");
	tick_select = getPositiveIntegerWithZero();
	if (tick_select != 0)
	{
		arrTick = findTicketIndexByTickNum(tick_select, data->tickets, data->TICKET_MAX_SIZE);
		printf("\n");
		if (arrTick >= 0)
		{
			displayTicketMessages(&data->tickets[arrTick]);
		}
		else
		{
			printf("ERROR: Invalid ticket number.\n\n");
			pauseExecution();
		}
	}
	return tick_select;
}

void agentDisplayTicket(const int i, const ACCOUNTTICKETINGDATA* data)
{
	printf("%06d %5d ", data->tickets[i].tick_num, data->tickets[i].cust_acc_num);
	printf("%-15s ", data->tickets[i].messages[0].name);
	if (data->tickets[i].status)
	{
		printf("ACTIVE ");
	}
	else
	{
		printf("CLOSED ");
	}
	printf("%-30s    %2d\n", data->tickets[i].subj_line, data->tickets[i].counter);
}

int accountVerification(int* selection, ACCOUNTTICKETINGDATA* data)
{
	int loop, account_num, array_pos, count = 3;
	char user_login[101];
	char password[101];
	do
	{
		loop = 0;
		printf("Enter the account#: ");
		account_num = getPositiveInteger();
		array_pos = findAccountIndexByAcctNum(account_num, data->accounts, data->ACCOUNT_MAX_SIZE, 0);
		printf("User Login    : ");
		getCString(user_login, 1, 100);
		printf("Password      : ");
		getCString(password, 1, 100);
		//if this is true, they can't login
		if (array_pos == -1)
		{
			//this will allow us to return to the beginning of login or exit page
			loop = 1;
		}
		//this will compare if the entered credentials match an account
		if (!strcmp(user_login, data->accounts[array_pos].login.login_name)
			&& !strcmp(password, data->accounts[array_pos].login.password))
		{
			//if it matches we set count to 0 and we will return the array_pos to login
			printf("\n");
			*selection = array_pos;
			count = 0;
		}
		else
		{
			count -= 1;
			loop = 1;
			printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", count);
		}
		//This allows for 3 attempts before going back to login or exit page
	} while (count > 0);
	if (count == 0 && loop == 1)
	{
		printf("ERROR:  Login failed!\n\n");
		pauseExecution();
	}
	return loop;
}

void customerNewTicket(TICKET* tickets, const int TickArrSize, const ACCOUNT* data_current_acc)
{
	int i, empty_slot, count_tick, biggest_tick_num;
	//loop through the array to find the empty slot
	for (i = 0; i < TickArrSize && tickets[i].tick_num != 0; i++)
	{
		//if the slot is not empty, it will continue looping
		//if slot is empty, for loop will exit after increasing i by 1
	}
	empty_slot = i;
	count_tick = 0;
	//this code will figure out the next account number to generate
	biggest_tick_num = tickets[0].tick_num;
	for (i = 1; i < TickArrSize; i++)
	{
		if (tickets[i].tick_num > 0)
		{
			++count_tick;
		}
		if (biggest_tick_num < tickets[i].tick_num)
		{
			biggest_tick_num = tickets[i].tick_num;
		}
	}
	biggest_tick_num += 1;

	if (empty_slot < TickArrSize)
	{
		newTicket(&tickets[empty_slot], biggest_tick_num, data_current_acc->login.name);
		tickets[empty_slot].cust_acc_num = data_current_acc->account_num;
		tickets[empty_slot].messages[0].account_type = 'C';
		printf("*** New ticket created! ***\n\n");
	}
	else
	{
		printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
	}
	pauseExecution();
}

void customerModifyActiveTicket(TICKET* tickets, const int arrSize, const ACCOUNT* data_current_acc)
{
	int tick_select, arrTick, select_mod;
	printf("Enter ticket number: ");
	tick_select = getPositiveInteger();
	arrTick = findTicketIndexByTickNum(tick_select, tickets, arrSize);
	printf("\n");
	if (arrTick >= 0)
	{
		if (tickets[arrTick].cust_acc_num == data_current_acc->account_num && tickets[arrTick].status)
		{
			do
			{
				printf("----------------------------------------\n");
				printf("Ticket %06d - Update Options\n", tickets[arrTick].tick_num);
				printf("----------------------------------------\n");
				printf("Status  : ");
				if (tickets[arrTick].status)
				{
					printf("ACTIVE\n");
				}
				else
				{
					printf("CLOSED\n");
				}
				printf("Subject : %s\n", tickets[arrTick].subj_line);
				printf("----------------------------------------\n");
				printf("1) Modify the subject\n");
				printf("2) Add a message\n");
				printf("3) Close ticket\n");
				printf("0) Done\n");
				printf("Selection: ");
				select_mod = getIntFromRange(0, 3);
				printf("\n");
				switch (select_mod)
				{
				case 1:
					modTickSubject(&tickets[arrTick]);
					break;
				case 2:
					if (tickets[arrTick].counter < 20)
					{
						addTickMessage(&tickets[arrTick], data_current_acc->login.name, data_current_acc->account_type);
					}
					else
					{
						printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
					}
					break;
				case 3:
					if (tickets[arrTick].status)
					{
						closeTick(&tickets[arrTick], data_current_acc->login.name, data_current_acc->account_type);
						if (!tickets[arrTick].status)
						{
							select_mod = 0;
						}
					}
					else
					{
						printf("ERROR: Ticket is already closed!\n\n");
						pauseExecution();
					}
					break;
				}
			} while (select_mod != 0);
		}
		else if (!tickets[arrTick].status)
		{
			printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
		}
		else if (tickets[arrTick].cust_acc_num != data_current_acc->account_num)
		{
			printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
		}
	}
	else
	{
		printf("ERROR: Invalid ticket number.\n\n");
	}

	pauseExecution();
}

void customerListTickets(TICKET* tickets, const int TickArrSize, const ACCOUNT* data_current_acc)
{
	int i, tick_select, arrTick;
	do
	{
		printf("------ ------ ------------------------------ --------\n");
		printf("Ticket Status Subject                        Messages\n");
		printf("------ ------ ------------------------------ --------\n");
		for (i = 0; i < TickArrSize; ++i)
		{
			if (tickets[i].cust_acc_num == data_current_acc->account_num)
			{
				printf("%06d ", tickets[i].tick_num);
				if (tickets[i].status)
				{
					printf("ACTIVE ");
				}
				else
				{
					printf("CLOSED ");
				}
				printf("%-30s    %2d\n", tickets[i].subj_line, tickets[i].counter);
			}
		}
		printf("------ ------ ------------------------------ --------\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		tick_select = getPositiveIntegerWithZero();
		if (tick_select != 0)
		{

			arrTick = findTicketIndexByTickNum(tick_select, tickets, TickArrSize);
			printf("\n");
			if (arrTick >= 0 && tickets[arrTick].cust_acc_num == data_current_acc->account_num)
			{
				displayTicketMessages(&tickets[arrTick]);
			}
			else if (arrTick >= 0 && tickets[arrTick].cust_acc_num != data_current_acc->account_num)
			{
				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				pauseExecution();
			}
			else
			{
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();
			}
		}
	} while (tick_select > 0);
	printf("\n");
}