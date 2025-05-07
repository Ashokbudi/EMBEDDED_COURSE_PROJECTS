#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
	FILE* fptr = fopen("contact.csv","w");
	fprintf(fptr,"%d\n",addressBook->contactCount);
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fptr,"%s,",addressBook->contacts[i].name);
		fprintf(fptr,"%s,",addressBook->contacts[i].phone);
		fprintf(fptr,"%s,",addressBook->contacts[i].email);
		fprintf(fptr,"%s\n",addressBook->contacts[i].group);
	}
	fclose(fptr);	
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
 	   
	FILE* fptr = fopen("contact.csv","r");
	fscanf(fptr,"%d\n",&addressBook->contactCount);
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fscanf(fptr," %[^,],",addressBook->contacts[i].name);
		fscanf(fptr," %[^,],",addressBook->contacts[i].phone);
		fscanf(fptr," %[^,],",addressBook->contacts[i].email);
		fscanf(fptr," %[^\n]",addressBook->contacts[i].group);
		fgetc(fptr);
	}
	fclose(fptr);	

}
