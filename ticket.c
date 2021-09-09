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

int loadTickets(TICKET* tickets, int size)
{
	int j, i = 0;
	int empty = 0;
	int temp_status;
	FILE* fp = NULL;
	fp = fopen("tickets.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp) && i < size)
		{
			fscanf(fp, "%d%*c%d%*c%d%*c%[^|]%*c%d%*c",
				&tickets[i].tick_num,
				&tickets[i].cust_acc_num,
				&temp_status,
				tickets[i].subj_line,
				&tickets[i].counter);
			tickets[i].status = temp_status;
			j = 0;
			while (j < (tickets[i].counter))
			{
				fscanf(fp, "%c%*c%[^|]%*c%[^|]%*c",
					&tickets[i].messages[j].account_type,
					tickets[i].messages[j].name,
					tickets[i].messages[j].msg_details);
				j++;
			}
			if (tickets[i].tick_num == 0)
			{
				++empty;
			}
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	i = i - empty;
	return i;
}

int saveTickets(TICKET* tickets, int size)
{
	int j, i = 0;
	int tickets_saved = 0;
	FILE* fp = NULL;
	fp = fopen("tickets.txt", "w");
	if (fp != NULL)
	{
		while (i < size)
		{
			if (tickets[i].tick_num > 0)
			{
				tickets_saved++;
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
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return tickets_saved;
}

int archClosedTickets(TICKET* tickets, const int TickArrSize)
{
	int j, i = 0;
	int closedTicks = 0;
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "a");
	if (fp != NULL)
	{
		while (!feof(fp) && i < TickArrSize)
		{
			if (!tickets[i].status && tickets[i].tick_num > 0)
			{
				closedTicks++;
				fprintf(fp, "%d|%d|%d|%s|%d|",
					tickets[i].tick_num,
					tickets[i].cust_acc_num,
					tickets[i].status,
					tickets[i].subj_line,
					tickets[i].counter);
				tickets[i].tick_num = 0;
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
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return closedTicks;
}

void archTicketsStats()
{
	TICKET tickets[30] = { {0} };
	int j, i = 0;
	int temp_status;
	int total_messages = 0;
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d%*c%d%*c%d%*c%[^|]%*c%d%*c",
				&tickets[i].tick_num,
				&tickets[i].cust_acc_num,
				&temp_status,
				tickets[i].subj_line,
				&tickets[i].counter);
			tickets[i].status = temp_status;
			j = 0;
			while (j < (tickets[i].counter))
			{
				fscanf(fp, "%c%*c%[^|]%*c%[^|]%*c",
					&tickets[i].messages[j].account_type,
					tickets[i].messages[j].name,
					tickets[i].messages[j].msg_details);
				j++;
			}
			total_messages += j;
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	--i;
	printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", i, total_messages);
}

void newTicket(TICKET* tick, int new_tick_num, const char* name)
{
	int i;
	tick->tick_num = new_tick_num;
	printf("New Ticket (Ticket#:%06d)\n", new_tick_num);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(tick->subj_line, 1, 30);
	printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(tick->messages[0].msg_details, 1, 150);
	printf("\n");

	tick->status = 1;
	tick->counter = 1;
	for (i = 0; i < 31; ++i)
	{
		tick->messages[0].name[i] = name[i];
	}
}

void modTickSubject(TICKET* tick)
{
	printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
	getCString(tick->subj_line, 1, 30);
	printf("\n");
}

void addTickMessage(TICKET* tick, const char* name, const char account_type)
{
	printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(tick->messages[tick->counter].msg_details, 1, 150);
	tick->messages[tick->counter].account_type = account_type;
	strcpy(tick->messages[tick->counter].name, name);
	tick->counter += 1;
	printf("\n");
}

void closeTick(TICKET* tick, const char* name, char account_type)
{
	char close, close_msg;
	//int i;
	printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
	close = getCharOption("YN");
	printf("\n");
	switch (close)
	{
	case 'Y':
		
		if (tick->counter < 20)
		{
			printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
			close_msg = getCharOption("YN");
			printf("\n");
			if (close_msg == 'Y')
			{
				printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(tick->messages[tick->counter].msg_details, 1, 150);
				strcpy(tick->messages[tick->counter].name, name);
				tick->messages[tick->counter].account_type = account_type;
				/*for (i = 0; i < 31; ++i)
				{
					tick->messages[tick->counter].name[i] = name[i];
				}*/
				tick->counter += 1;
				printf("\n");
			}
		}
		
		tick->status = 0;
		printf("*** Ticket closed! ***\n\n");
		break;
	case 'N':
		break;
	}


}

void openTick(TICKET* tick)
{
	char close;
	printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
	close = getCharOption("YN");

	switch (close)
	{
	case 'Y':
		tick->status = 1;
		printf("\n*** Ticket re-opened! ***\n");
		break;
	case 'N':
		break;
	}

	printf("\n");
}