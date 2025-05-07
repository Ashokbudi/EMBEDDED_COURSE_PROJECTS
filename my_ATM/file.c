#include <stdio.h>
#include "file.h"

void saveContactsToFile(acct *account) 
{
	FILE* fptr = fopen("account.csv","w");
	fprintf(fptr,"%d\n",account->total_contacts);
	for(int i=0;i<account->total_contacts;i++)
	{
		fprintf(fptr,"%s,",account->accounts[i].name);
		fprintf(fptr,"%s,",account->accounts[i].mobile);
		fprintf(fptr,"%f,",account->accounts[i].curr_bal);
		fprintf(fptr,"%d,",account->accounts[i].password);
		fprintf(fptr,"%d\n",account->accounts[i].x);
	}
	fclose(fptr);	
  
}

void loadContactsFromFile(acct *account) 
{
 	   
	FILE* fptr = fopen("account.csv","r");
	fscanf(fptr,"%d\n",&account->total_contacts);
	for(int i=0;i<account->total_contacts;i++)
	{
		fscanf(fptr," %[^,],",account->accounts[i].name);
		fscanf(fptr," %[^,],",account->accounts[i].mobile);
		fscanf(fptr," %f,",&account->accounts[i].curr_bal);
		fscanf(fptr," %d,",&account->accounts[i].password);
		fscanf(fptr," %d\n",&account->accounts[i].x);
		
	}
	fclose(fptr);	

}
