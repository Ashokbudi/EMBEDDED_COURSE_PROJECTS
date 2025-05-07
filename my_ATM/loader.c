#include<stdio.h>
#include "account.h"
int main()
{
	acct account;
	initialise(&account);
	int i=1;
	printf("\t\t\t\t:::WELCOME TO ATM:::\n");
	printf("\n\nDONT KNOW HOW TO USE PRESS 1 TO READ INSTRUCTION OR ELSE PRESS 0 FOR CONTINUE: ");
	int option;
	scanf("%d",&option);
	getchar();
	if(option == 1)
	{
		rules();
		printf("After reading press enter to continue: ");
		getchar();
	}
	printf("\n\nChoose your language\n");
	printf("1. Telugu\n2. English\nEnter your choice -------> ");
	int opt;
	scanf("%d",&opt);
	int service_opt;
	if(opt==2)
	{
		while(i)
		{
			printf(":::HERE IS YOUR MENU:::\n");
			printf("1. Balance Enquiry\n2. Withdraw Amount\n3. Deposit Amount\n4. Close Account\n5. Exit\nEnter your choice -----> ");
			scanf("%d",&service_opt);
			switch(service_opt)
			{
				case 1:
					check_balance(&account);
					break;
				case 2:
					with_draw(&account);
					break;
				case 3:
					deposit(&account);
					break;
				case 4:
					close_account(&account);
					break;
				case 5:
					printf("THANK YOU FOR CONTACTING US\n");
					saveAndExit(&account);
					i=0;
			}
		}
	}
	else if(opt ==1)
	{

		while(i)
		{
			printf(":::ఇక్కడ మీ మెనూ ఉం:::\n");
		 printf("1. బ్యాలెన్స్ తనిఖీ\n2. నగదు ఉపసంహారం\n3. నగదు డిపాజిట్\n4. ఖాతాను మూసివేయు5. ఎగ్జిట్\\n5.మీ ఎంపిక నమోదు చేయండి -----> ");
			scanf("%d",&service_opt);
			switch(service_opt)
			{
				case 1:
					check_tel_balance(&account);
					break;
				case 2:
					with_tel_draw(&account);
					break;
				case 3:
					deposit_tel(&account);
					break;
				case 4:
					close_tel_account(&account);
					break;
				case 5:
					saveAndExit(&account);
					i=0;
			}
		}
	}
}






