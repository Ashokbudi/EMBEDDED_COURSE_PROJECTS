#include<stdio.h>
#include "account.h"
#include<string.h>
#include "file.h"
void initialise(acct *account)
{
	account->total_contacts=0;
	loadContactsFromFile(account);
}
void saveAndExit(acct* account)
{
	saveContactsToFile(account);
}
void rules()
{
	FILE* fptr = fopen("rules.txt","r");
	char ch;
	while((ch = fgetc(fptr)) != -1)
	{
		fputc(ch,stdout);
	}
}
int search_name(acct *account,char* name,int* index)
{
	for(int i=0;i<(account->total_contacts);i++)
	{
		if(strcmp(account->accounts[i].name,name) == 0)
		{
			*index =i;
			return 1;
		}
	}
	return 0;
}
int search_mobile(acct *account,char* mobile,int* index)
{
	for(int i=0;i<(account->total_contacts);i++)
	{
		if(strcmp(account->accounts[i].mobile,mobile) == 0)
		{
			*index =i;
			return 1;
		}
	}
	return 0;
}
void print_slip(int index,acct* account)
{
							printf("+---------------------------------------+\n");
							printf("|                                       |\n");
							printf("|         \033[0;43mWELCOME TO ASHOK ATM\033[0m          |\n");
							printf("|                                       |\n");
							printf("|  \033[0;34mDATE\033[0m:%s                     |\n",__DATE__);
							printf("|  \033[0;34mTIME\033[0m:%s                        |\n",__TIME__);
							printf("|                                       |\n");
							printf("|  \033[0;34mNAME\033[0m:%-20s            |\n",account->accounts[index].name);
							printf("|  \033[0;34mCONTACT\033[0m:%-15s              |\n",account->accounts[index].mobile);
							printf("|                                       |\n");
							printf("|         \033[0;34mBALANCE\033[0m: %-10f         |\n",account->accounts[index].curr_bal);
							printf("|                                       |\n");
							printf("|        \033[0;42mTHANKYOU FOR CONTACTING US\033[0m     |\n");
							printf("|                                       |\n");
							printf("+---------------------------------------+\n\033[0m");

}
void check_balance(acct *account)
{
	printf("\nPlease enter by which reference you want to login\n");
	printf("1. name\n2. mobile number\nchoice ----> ");
	int opt;
	scanf("%d",&opt);
	int index;
	char name[20];
	char mobile[20];
	int i=1;
	int pin;
	int chances=3;
	char ch11;
	if(opt==1)
	{
		while(i)
		{
			printf("Enter the name of the account holder: ");
			getchar();
			scanf("%[^\n]",name);
			int res = search_name(account,name,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to check your balance: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("your current balance is :  ");
							printf("%f\n",account->accounts[index].curr_bal);
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                               		chances =0;
						}
						else
						{
							chances--;
							account->accounts[index].x = chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
					i=0;
				}
				else
				{
					printf("You cant access your atm card for 24 hours as you entered 3 incorrect pins\n");
							printf("\a");
				}
			}
			else
			{
				printf("account not found --> please retype your name\n");
							printf("\a");
			}
		}
	}
	else
	{
		while(i)
		{
			printf("Enter the mobile number of the account holder: ");
			getchar();
			scanf("%[^\n]",mobile);
			int res = search_mobile(account,mobile,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to check your balance: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("your current balance is :  ");
							printf("%f\n",account->accounts[index].curr_bal);
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
							chances =0;
						}
						else
						{
							chances--;
							account->accounts[index].x=chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
					printf("You cant access your atm card for 24 hours as you entered 3 incorrect pins\n");
							printf("\a");
				}	
				i=0;
			}
			else
			{
				printf("account not found--> please retype your mobile number\n");
							printf("\a");
			}
		}
	}
}
void with_draw(acct* account)
{
	printf("\nPlease enter by which reference you want to login\n");
	printf("1. name\n2. mobile number\nchoice ----> ");
	int opt;
	scanf("%d",&opt);
	int index;
	char name[20];
	char mobile[20];
	char ch11;
	int i=1;
	int pin;
	int chances=3;
	int amount;
	char ch;
	if(opt==1)
	{
		while(i)
		{
			printf("Enter the name of the account holder: ");
			getchar();
			scanf("%[^\n]",name);
			int res = search_name(account,name,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
					printf("please enter your pin to withdraw your amount: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("Enter the amount that you want to withdraw: ");
							scanf("%d",&amount);
							if(amount <= account->accounts[index].curr_bal)
							{
								printf("your amount is succesfully withdrawn\n");
								account->accounts[index].curr_bal = account->accounts[index].curr_bal - amount;
								printf("do you want to check your balance press y to yes n to no: ");
								getchar();
								scanf("%c",&ch);
								if(ch=='y')
								{
									printf("your current balance :  ");
									printf("%f\n",account->accounts[index].curr_bal);
								}
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
								chances=0;
							}
						}
						else
						{
							chances--;
							account->accounts[index].x=chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
							printf("chances are over try after 24 hours\n");
							printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your name\n");
							printf("\a");
			}
		}
	}
	else
	{
		while(i)
		{
			printf("Enter the mobile number of the account holder: ");
			getchar();
			scanf("%[^\n]",mobile);
			int res = search_mobile(account,mobile,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to withdraw your amount: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("Enter the amount that you want to withdraw: ");
							scanf("%d",&amount);
							if(amount <= account->accounts[index].curr_bal)
							{
								printf("your amount is succesfully withdrawn\n");
								account->accounts[index].curr_bal = account->accounts[index].curr_bal - amount;
								printf("do you want to check your balance press y to yes n to no: ");
								getchar();
								scanf("%c",&ch);
								if(ch=='y')
								{
									printf("your current balance :  ");
									printf("%f\n",account->accounts[index].curr_bal);
								}
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
								chances=0;
							}
						}
						else
						{
							chances--;
							account->accounts[index].x = chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
					printf("your chances completed and freezed your atm services for 24 hours\n");
							printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your mobile number\n");
							printf("\a");
			}
		}
	}
}
void deposit(acct* account)
{
	printf("\nPlease enter by which reference you want to login\n");
	printf("1. name\n2. mobile number\nchoice ----> ");
	int opt;
	scanf("%d",&opt);
	int index;
	char name[20];
	char mobile[20];
	int i=1;
	int pin;
	char ch11;
	int chances=3;
	int amount;
	char ch;
	if(opt==1)
	{
		while(i)
		{
			printf("Enter the name of the account holder: ");
			getchar();
			scanf("%[^\n]",name);
			int res = search_name(account,name,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to deposit your amount: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("Enter the amount that you want to deposit: ");
							scanf("%d",&amount);
							printf("your amount is succesfully deposit\n");
							account->accounts[index].curr_bal = account->accounts[index].curr_bal + amount;
							printf("do you want to check your balance press y to yes n to no: ");
							getchar();
							scanf("%c",&ch);
							if(ch=='y')
							{
								printf("your current balance :  ");
								printf("%f\n",account->accounts[index].curr_bal);
							}
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
							chances=0;
						
						}
						else
						{
							chances--;
							account->accounts[index].x = chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
					printf("your chances for today is freezed for 24 hours\n");
							printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your name\n");
							printf("\a");
			}
		}
	}
	else
	{
		while(i)
		{
			printf("Enter the mobile number of the account holder: ");
			getchar();
			scanf("%[^\n]",mobile);
			int res = search_mobile(account,mobile,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to deposit your amount: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							printf("Enter the amount that you want to deposit: ");
							scanf("%d",&amount);
							printf("your amount is succesfully deposited\n");
							account->accounts[index].curr_bal = account->accounts[index].curr_bal + amount;
							printf("do you want to check your balance press y to yes n to no: ");
							getchar();
							scanf("%c",&ch);
							if(ch=='y')
							{
								printf("your current balance :  ");
								printf("%f\n",account->accounts[index].curr_bal);
							}
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
							chances=0;
						
						}
						else
						{
							chances--;
							account->accounts[index].x = chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
					printf("you cant access your account for 24 hours\n");
							printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your mobile number\n");
							printf("\a");
			}
		}
	}
}
void close_account(acct* account)
{
	printf("\nPlease enter by which reference you want to login\n");
	printf("1. name\n2. mobile number\nchoice ----> ");
	int opt;
	scanf("%d",&opt);
	int index;
	char name[20];
	char mobile[20];
	int i=1;
	int pin;
	int chances=3;
	int amount;
	char ch;
	char ch11;
	if(opt==1)
	{
		while(i)
		{
			printf("Enter the name of the account holder: ");
			getchar();
			scanf("%[^\n]",name);
			int res = search_name(account,name,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to close your amount: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{
							Account temp = account->accounts[index];
							account->accounts[index] = account->accounts[account->total_contacts-1];
							account->accounts[account->total_contacts-1] = temp;
							account->total_contacts--;
							chances=0;
						
						}
						else
						{
							chances--;
							account->accounts[index].x=chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
						}
					}
				}
				else
				{
					printf("you are not having access to your account for 24 hours\n");
							printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your name\n");
							printf("\a");
			}
		}
	}
	else
	{
		while(i)
		{
			printf("Enter the mobile number of the account holder: ");
			getchar();
			scanf("%[^\n]",mobile);
			int res = search_mobile(account,mobile,&index);
			if(res==1)
			{
				if(account->accounts[index].x >=1)
				{
					while(chances > 0)
					{
						printf("please enter your pin to close your account: ");
						scanf("%d",&pin);
						if(pin == account->accounts[index].password)
						{	
							Account temp = account->accounts[index];
							account->accounts[index] = account->accounts[account->total_contacts-1];
							account->accounts[account->total_contacts-1] = temp;
							account->total_contacts--;
							chances=0;
						}
						else
						{
							chances--;
							account->accounts[index].x = chances;
							printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
							printf("\a");
							printf("\a");
						}
					}
				}
				else
				{
					printf("you dont have acces to your account for 24 hours\n");
					printf("\a");
				}
				i=0;
			}
			else
			{
				printf("account not found--> please retype your mobile number\n");
							printf("\a");
			}
		}
	}
}
int search_tname(acct *account,char* name,int* index)
{
        for(int i=0;i<(account->total_contacts);i++)
        {
                if(strcmp(account->accounts[i].name,name) == 0)
                {
                        *index =i;
                        return 1;
                }
        }
        return 0;
}
int search_tmobile(acct *account,char* mobile,int* index)
{
        for(int i=0;i<(account->total_contacts);i++)
        {
                if(strcmp(account->accounts[i].mobile,mobile) == 0)
                {
                        *index =i;
                        return 1;
                }
        }
        return 0;
}
void check_tel_balance(acct *account)
{
        printf("\nమీరు లాగిన్ కావాలని కోరుకునే సూచికను నమోదు చేయండి\n");
        printf("1. పేరు2\n2. మొబైల్ నంబర్ \n3.మీ ఎంపిక నమోదు చేయండి ----> ");
        int opt;
        scanf("%d",&opt);
        int index;
        char name[20];
        char mobile[20];
        int i=1;
        int pin;
	char ch11;
        int chances=3;
        if(opt==1)
        {
                while(i)
                {
                        printf("ఖాతా యజమానివారి పేరు నమోదు చేయండి ");
                        getchar();
                        scanf("%[^\n]",name);
                        int res = search_tname(account,name,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("మీ బ్యాలెన్స్ను తనిఖీ చేయడానికి దయచేసి మీ పిన్ నమోదు చేయండి: """);
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("your current balance is :  ");
                                                printf("%f\n",account->accounts[index].curr_bal);
						
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                chances =0;
                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found --> please retype your name\n");
                        }
                }
        }
        else
        {
                while(i)
                {
                        printf("Enter the mobile number of the account holder: ");
                        getchar();
                        scanf("%[^\n]",mobile);
                        int res = search_tmobile(account,mobile,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin:");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("your current balance is :  ");
                                                printf("%f\n",account->accounts[index].curr_bal);
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                chances =0;
                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your mobile number\n");
                        }
                }
        }
}
void with_tel_draw(acct* account)
{
        printf("\nమీరు లాగిన్ కావాలని కోరుకునే సూచికను నమోదు చేయండి\n");
        printf("1. పేరురు2\n. మొబైల్ \n3. మీ ఎంపిక నమోదు చేయండి ----> ");
        int opt;
        scanf("%d",&opt);
        int index;
        char name[20];
        char mobile[20];
        int i=1;
        int pin;
        int chances=3;
        int amount;
	char ch11;
        char ch;
        if(opt==1)
        {
                while(i)
                {
                        printf("ఖాతా యజమానివారి పేరు నమోదు చేయండి: ");
                        getchar();
                        scanf("%[^\n]",name);
                        int res = search_tname(account,name,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to withdraw your amount: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("Enter the amount that you want to withdraw: ");
                                                scanf("%d",&amount);
                                                if(amount <= account->accounts[index].curr_bal)
                                                {
                                                        printf("your amount is succesfully withdrawn\n");
                                                        account->accounts[index].curr_bal = account->accounts[index].curr_bal - amount;
                                                        printf("do you want to check your balance press y to yes n to no: ");
                                                        getchar();
                                                        scanf("%c",&ch);
                                                        if(ch=='y')
                                                        {
                                                                printf("your current balance :  ");
                                                                printf("%f\n",account->accounts[index].curr_bal);
                                                        }
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                        chances=0;
                                                }
                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your name\n");
                        }
                }
        }
        else
        {
                while(i)
                {
                        printf("Enter the mobile number of the account holder: ");
                        getchar();
                        scanf("%[^\n]",mobile);
                        int res = search_tmobile(account,mobile,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to withdraw your amount: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("Enter the amount that you want to withdraw: ");
                                                scanf("%d",&amount);
                                                if(amount <= account->accounts[index].curr_bal)
                                                {
                                                        printf("your amount is succesfully withdrawn\n");
                                                        account->accounts[index].curr_bal = account->accounts[index].curr_bal - amount;
                                                        printf("do you want to check your balance press y to yes n to no: ");
                                                        getchar();
                                                        scanf("%c",&ch);
                                                        if(ch=='y')
                                                        {
                                                                printf("your current balance :  ");
                                                                printf("%f\n",account->accounts[index].curr_bal);
                                                        }
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                        chances=0;
                                                }
                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your mobile number\n");
                        }
                }
        }
}
void deposit_tel(acct* account)
{
        printf("\nమీరు లాగిన్ కావాలని కోరుకునే సూచికను నమోదు చేయండి\n");
        printf("1. పేరురు2\n. మొబైల్ \n3. మీ ఎంపిక నమోదు చేయండి ----> ");
        int opt;
        scanf("%d",&opt);
        int index;
        char name[20];
        char mobile[20];
        int i=1;
        int pin;
        int chances=3;
        int amount;
	char ch11;
        char ch;
        if(opt==1)
        {
                while(i)
                {
                        printf("ఖాతా యజమానివారి పేరు నమోదు చేయండి: ");
                        getchar();
                        scanf("%[^\n]",name);
                        int res = search_tname(account,name,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to deposit your amount: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("Enter the amount that you want to deposit: ");
                                                scanf("%d",&amount);
                                                        printf("your amount is succesfully deposit\n");
                                                        account->accounts[index].curr_bal = account->accounts[index].curr_bal + amount;
                                                        printf("do you want to check your balance press y to yes n to no: ");
                                                        getchar();
                                                        scanf("%c",&ch);
                                                        if(ch=='y')
                                                        {
                                                                printf("your current balance :  ");
                                                                printf("%f\n",account->accounts[index].curr_bal);
                                                        }
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                        chances=0;

                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your name\n");
                        }
                }
        }
        else
        {
                while(i)
                {
                        printf("Enter the mobile number of the account holder: ");
                        getchar();
                        scanf("%[^\n]",mobile);
                        int res = search_tmobile(account,mobile,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to deposit your amount: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                printf("Enter the amount that you want to deposit: ");
                                                scanf("%d",&amount);
                                                        printf("your amount is succesfully deposited\n");
                                                        account->accounts[index].curr_bal = account->accounts[index].curr_bal + amount;
                                                        printf("do you want to check your balance press y to yes n to no: ");
                                                        getchar();
                                                        scanf("%c",&ch);
                                                        if(ch=='y')
                                                        {
                                                                printf("your current balance :  ");
                                                                printf("%f\n",account->accounts[index].curr_bal);
                                                        }
							printf("you want to print slip(y-yes || n-no): ");
							getchar();
							scanf("%c",&ch11);
							if(ch11=='y')
							{
								print_slip(index,account);
							}
                                                        chances=0;

                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your mobile number\n");
                        }
                }
        }
}
void close_tel_account(acct* account)
{
        printf("\nమీరు లాగిన్ కావాలని కోరుకునే సూచికను నమోదు చేయండి\n");
        printf("1. పేరురు2\n. మొబైల్ నంబ\n3. మీ ఎంపిక నమోదు చేయండి ----> ");
        int opt;
        scanf("%d",&opt);
        int index;
        char name[20];
        char mobile[20];
        int i=1;
        int pin;
        int chances=3;
        int amount;
        char ch;
        if(opt==1)
        {
                while(i)
                {
                        printf("ఖాతా యజమానివారి పేరు నమోదు చేయండి: ");
                        getchar();
                        scanf("%[^\n]",name);
                        int res = search_tname(account,name,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to close your amount: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                Account temp = account->accounts[index];
                                                account->accounts[index] = account->accounts[account->total_contacts-1];
                                                account->accounts[account->total_contacts-1] = temp;
                                                account->total_contacts--;
                                                printf("your account has been succesfully closed\n");
                                                chances=0;

                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your name\n");
                        }
                }
        }
        else
        {
                while(i)
                {
                        printf("Enter the mobile number of the account holder: ");
                        getchar();
                        scanf("%[^\n]",mobile);
                        int res = search_tmobile(account,mobile,&index);
                        if(res==1)
                        {
                                while(chances > 0)
                                {
                                        printf("please enter your pin to close your account: ");
                                        scanf("%d",&pin);
                                        if(pin == account->accounts[index].password)
                                        {
                                                Account temp = account->accounts[index];
                                                account->accounts[index] = account->accounts[account->total_contacts-1];
                                                account->accounts[account->total_contacts-1] = temp;
                                                account->total_contacts--;
                                                printf("your account has been succesfully closed\n");
                                                chances=0;
                                        }
                                        else
                                        {
                                                chances--;
                                                printf("invalid pin entered please re-try it you have only %d choices\n\n",chances);
                                        }
                                }
                                i=0;
                        }
                        else
                        {
                                printf("account not found--> please retype your mobile number\n");
                        }
                }
        }
}
