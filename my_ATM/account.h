#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<stdio.h>

typedef struct Account
{
	char name[20];
	float curr_bal;
	int password;
	char mobile[20];
	int x;
}Account;

typedef struct
{
	Account accounts[100];
	int total_contacts;
}acct;

void check_balance(acct *account);
void with_draw(acct *account);
void deposit(acct *account);
void saveAndExit(acct *account);
void load_contacts(acct *account);
void initialise(acct *account);
void close_account(acct *account);
void check_tel_balance(acct *account);
void with_tel_draw(acct *account);
void deposit_tel(acct *account);
void saveAndExit_tel(acct *account);
void close_tel_account(acct* account);
void rules(void);
#endif

