
#include "contact.h"
#include "file.h"

int main()
{
	AddressBook addressBook;
	//saveContactsToFile(&addressBook);
	initialize(&addressBook);
	int i=1;
	while(i)
	{
		printf("\nAddress Book Menu:\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		int opt;
		int opt1;
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
				createContact(&addressBook);
				break;
			case 2:
				searchContact(&addressBook);
				break;
			case 3:
				editContact(&addressBook);
				break;
			case 4:
				deleteContact(&addressBook);
				break;
			case 5:
				printf("1. list all contacts\n2. list contacts from specific group\n");
				printf("Enter option: ");
				scanf("%d",&opt1);
				if(opt1==1)
				{
					listContacts(&addressBook);
				}
				else
				{
					list_group(&addressBook);
				}
				break;
			case 6:
				saveAndExit(&addressBook);
				i=0;
				break;
			default:
				printf("invalid option\n");
		}
	}
}
