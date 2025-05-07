#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)		//calling function for printing all details 
{

		printf("+------+---------------+-----------+-------------------------+---------------+\n");
		printf("|s.no  |name           |mobile     |email                    |group          |\n");
		printf("+------+---------------+-----------+-------------------------+---------------+\n");
	for(int i=0;i<(addressBook->contactCount);i++)	//running loop untill the array last  elemenmt
	{
		printf("%-6d |%-15s|%-11s|%-25s|%-15s|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,addressBook->contacts[i].group);
		printf("+------+---------------+-----------+-------------------------+---------------+\n");
	}
}
void group_check(AddressBook* addressBook,char* str)
{

		printf("+------+---------------+-----------+-------------------------+---------------+\n");
		printf("|s.no  |name           |mobile     |email                    |group          |\n");
		printf("+------+---------------+-----------+-------------------------+---------------+\n");
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(addressBook->contacts[i].group,str)==0)
		{

		printf("%-6d |%-15s|%-11s|%-25s|%-15s|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,addressBook->contacts[i].group);
srand(time(0));		printf("+------+---------------+-----------+-------------------------+---------------+\n");
		}
	}
}			
void list_group(AddressBook *addressBook)
{
	printf("1. family\n2. friends\n3. colleagues\n4. company\n5. others\n");
	printf("Enter your option: \n");
	int opt1;
	scanf("%d",&opt1);
	//char ch[20];
	switch(opt1)
	{
		case 1:
			group_check(addressBook,"family");
			break;
		case 2:
			group_check(addressBook,"friends");
			break;
		case 3:
			group_check(addressBook,"colleagues");
			break;
		case 4:
			group_check(addressBook,"company");
			break;
		case 5:
			group_check(addressBook,"others");
			break;
	}
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int check_name(char* name)		//checking that it is a valid name or not
{
	int i=0;
	int flag=0;
	while(name[i])
	{
		int res = isalpha(name[i]);			//calling isalpha function to check
		if(res==0 && name[i] != ' ')
		{
			flag=1;					//if val occurs then it is not valid name
			break;
		}
		i++;
	}
	if(flag==1)
	{
		return 0;			//if not return 0
	}
	else
	{
		return 1;				//if all are alphabetical characters then return 1 
	}
}

int check_number(char* number)
{
	int len = strlen(number);		//checking length of the number because number shoild be equals to 10
	if(len!=10)
	{
		return 0;    			//if not return 0
	}
	int i=0;
	int flag=0;
	while(number[i])
	{
		if(isdigit(number[i]))
		{
			i++;			//checking all the characters entered is digits are not
		}
		else
		{
			return 0;		// if not return 0
		}
	}
	return 1;				//if all conditions satisfies then return 1
}
	
int check_mail(char* mail)		//checking email
{
	int i=0;
	int alcount=0;
	int at_the=0;
	while(mail[i])
	{
		if(mail[i] == '@')     		//checking characters upto @ all are lower case or not
		{
			at_the =1;		//if found make at_the =1
			break;
		}
		else if(islower(mail[i]))
		{
			alcount++;			//checking all are lower cases are not
			i++;
		}
		else if(isdigit(mail[i]))
		{
			i++;				//is any has digits
		}
		else
		{
			return 0;
		}
	}
	int len = strlen(mail);				//checking mail length that user entered
	char com[] = "moc.";
	int m = len-1;
	i=0;
	while(i<4)
	{
		if(mail[m] != com[i])			//checking either it has .com or not
		{
			return 0;
		}
		i++;
		m--;
	}
	if(at_the == 0 )
	{
		return 0;
	}
	else if(alcount == 0)			//if user doesnt enter a single lowercase then it returns 0
	{
		return 0;
	}
	return 1;
}
	
void createContact(AddressBook *addressBook)		//creating a contact
{
	getchar();
	int j=1;
	char name[20];
	while(j)
	{
		printf("Enter name of the person: ");
		scanf("%[^\n]",name);			//reading name from the user
		getchar();
		int res = check_name(name);		//checking name is valid or not
		if(res == 1)
		{
			strcpy(addressBook->contacts[addressBook->contactCount].name,name); //if it is valid storing in array
			j=0;
		}
		else
		{
			printf("invalid name entered: \nplease re_type the name: \n");    //else giving another chance to read input
		}
	}
    char number[11];							//reading number from the user
    j=1;
    while(j)
    {
    	    printf("Enter mobile number: ");
    	    scanf(" %[^\n]",number);
	    int flag=0;
	    int res1 = check_number(number);				//checking number is valid or not
	    if(res1 == 1)
	    {

		for(int i=0;i<addressBook->contactCount;i++)
		{
			int res = strcmp(addressBook->contacts[i].phone,number);			//checking if number exists
			if(res == 0)
			{
				flag=1;    		//if exits then giving another chance to read
				break;
			}
		}
		if(flag==0)
		{
		    strcpy(addressBook->contacts[addressBook->contactCount].phone,number); //if not store in the array
		    j=0;
		}
		else
		{
			printf("Name already exists please re-enter: \n");
		}
	    }
	    else
	    {
		    printf("person already exists\nenter a valid number: \n");   //if entered person not found
	    }
	    getchar();
    }
    char mail[20];			//reading mail from the user
    j=1;
    while(j)
    {
    	    printf("Enter email id: ");
    	    scanf(" %[^\n]",mail);
	    int flag1=0;
	    int res2 = check_mail(mail);		//checking the mail is valid or not
	    if(res2 == 1)
	    {

		for(int i=0;i<addressBook->contactCount;i++)
		{
			int res = strcmp(addressBook->contacts[i].email,mail);			//checking if the mail is already exists or not
			if(res == 0)
			{
				flag1=1;             //if exists give another chance to read
				break;
			}
		}
		if(flag1==0)
		{
		   strcpy(addressBook->contacts[addressBook->contactCount].email,mail);			//store in the array
		  j=0;
		}
		else
		{
			printf("person already exists\nre-enter again\n");
		}
	    }
	    else
	    {
		   printf("invalid email entered\nenter mail again: ");		//if entered person not found then print this
	    }
	    getchar();
    } 
    char group[30];
    printf("create new group and save:(press 1)\nsave in existing group:(press 2): ");
    int grp;
    scanf("%d",&grp);
    int option;
    int flag=0;
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
	    flag=0;
	    for(int j=0;j<addressBook->contactCount;j++)
	    {
		if(j<i)
		{
			if(addressBook->contacts[i].group == addressBook->contacts[j].group)
			{
				flag=1;
				break;
			}
		}
	    }
	    if(flag==0)
	    {
		    index++;
		    printf("\n\n%d\n",index);
	    }
    }
    if(grp == 1)
    {
	    if(index>5)
	    {
		    printf("groups exceeded--you have no longer access to create groups\n");
	    }
	    else
	    {
	printf("enter the new group name: ");
        scanf(" %[^\n]",group);
	strcpy(addressBook->contacts[addressBook->contactCount].group,group);
	    }
    }
    else if(grp == 2)
    {
	printf("1. family\n2. friends\n3. colleagues\n4. companies\n5. others\n");

        printf("enter the option to save: ");
	scanf("%d",&option);
	switch(option)
	{
	     case 1:
	     	    strcpy(addressBook->contacts[addressBook->contactCount].group,"family");
		    break;
	     case 2:
		    		    
	     	    strcpy(addressBook->contacts[addressBook->contactCount].group,"friends");
		    break;
	     case 3:

	     	    strcpy(addressBook->contacts[addressBook->contactCount].group,"colleagues");
		    break;
	     case 4:

	     	    strcpy(addressBook->contacts[addressBook->contactCount].group,"companies");
		    break;
	     case 5:

	     	    strcpy(addressBook->contacts[addressBook->contactCount].group,"others");
		    break;
	}
    }
    else
    {
	    printf("invalid\n");
    }
    (addressBook->contactCount)++;
    printf("val = %d",addressBook->contactCount);
}
int search_name(AddressBook* addressBook,char* name,int* count2,int* duplicates)
{
	
	int duplicate[10];
	int count=0;
	int flag=0;
	int real=-1;
	for(int i=0;i<(addressBook->contactCount);i++)  //running a loop
	{
		 int res = strcmp(addressBook->contacts[i].name,name);		//comparing user name with my addressbook names 
		 if(res == 0)
		 {
			 flag =1;
			 duplicate[count] = i;
			 count++;			 //if found then print details
		}
		
	}
	*count2 = count;
	 if(flag==1)
	{
	      for(int i=0;i<count;i++)
	      {
			real = duplicate[i];
			printf("\t\t:::USER DETAILS:::\n");
		        printf("\n------------------------------------------------\n\n");
			printf("name: %s\n",addressBook->contacts[real].name);
			printf("phone: %s\n",addressBook->contacts[real].phone);
		        printf("email: %s\n",addressBook->contacts[real].email);
			printf("\n------------------------------------------------\n");
	      }
	      return real;
	}
	else
       {
	    printf("Student not found: ");
	    return 0;
       }

}
int search_phone(AddressBook* addressBook,char* phone)
{
	int flag=0;
	int real;
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		int res = strcmp(addressBook->contacts[i].phone,phone);
		 if(res == 0)
		 {
			 flag =1;
			 real=i;
			 break;
		 }
	  }
	 if(flag==1)
	 {
		  printf("\t\t:::USER DETAILS:::\n");
		  printf("\n----------------------------------------------\n\n");
		 printf("name: %s\n",addressBook->contacts[real].name);
		   printf("phone: %s\n",addressBook->contacts[real].phone);
		    printf("email: %s\n",addressBook->contacts[real].email);
			printf("\n----------------------------------------------\n");
			return real;
	}
	 else
	 {
		 printf("Student not found: \n");
		 return 0;
	}
}
int search_email(AddressBook* addressBook,char* email)
{
	int flag=0;
	int real;
			  for(int i=0;i<(addressBook->contactCount);i++)
			  {
				 int res = strcmp(addressBook->contacts[i].email,email);
				 if(res == 0)
				 {
					 flag =1;
					 real=i;
					 break;
				 }
		          }
			  if(flag==1)
			  {
			     printf("\t\t:::USER DETAILS:::\n");
			     printf("\n--------------------------------------------------\n\n");
			     printf("name: %s\n",addressBook->contacts[real].name);
			     printf("phone: %s\n",addressBook->contacts[real].phone);
		             printf("email: %s\n",addressBook->contacts[real].email);
			     printf("\n--------------------------------------------------\n");
			     return real;
			  }
			  else
			  {
				  printf("Student not found: ");
				  return 0;
			  }
}
void searchContact(AddressBook *addressBook) 		//searching a specific contact
{
    int i=1;
    while(i)
    {
	    getchar();
	   printf("\n1. Search By name\n2. Search by mobile\n3. Search By email\n4. Exit\n");
	   printf("Enter your choice: ");					//asking user to enter which field we want to search
	   int opt;
	   //int duplicate[10];
	   int res;
	   //int count=0;
	   int flag=0;
	   char name[20];
	   char phone[20];
	   char email[20];
	   int real11;
	   int count2=0;
	   int dupli[30];
	   int scan = scanf("%d",&opt);
	   if(scan ==1 && opt >= 1 && opt <=4)
	   {							   //reading option from the user
	   switch(opt)
	   {
		   case 1:
			  printf("ENter name: ");
			  scanf(" %[^\n]",name);
			  real11 = search_name(addressBook,name,&count2,dupli);
			  break;
		   case 2:

			  printf("Enter mobile: ");
			  scanf(" %[^\n]",phone);
			  real11 = search_phone(addressBook,phone);
			  break;
		   case 3:

			  printf("Enter mail id: ");
			  scanf(" %[^\n]",email);
			  real11 = search_email(addressBook,email);
			  break;
		   case 4:
			  i=0;
	   }
	   }
	   else
	   {
		   printf("\ninvalid input enter please re-enter again\n");
	   }
    }
}	
void edit_fun(AddressBook* addressBook,int real)
{
	int i=1;
	int opt;
	char name1[20];
	char phone1[20];
	char email1[40];

				while(i)
				{
					printf("1. Edit name\n2. Edit phone\n3. Edit email\n4. Exit\n");
					printf("Enter option: ");
					//char name1[20];
					//char phone1[20];
					//char email1[20];
					int res;
					scanf("%d",&opt);
					switch(opt)
					{
					case 1:
						printf("Enter tha name: ");
						scanf(" %[^\n]",name1);
						res = check_name(name1);
						if(res == 0)
						{
							printf("invalid name entered: \n");
						}
						else
						{
							strcpy(addressBook->contacts[real].name,name1);
						}
				
						break;
					case 2:

						printf("Enter tha phone: ");
						scanf(" %[^\n]",phone1);
						res = check_number(phone1);
						if(res == 0)
						{
							printf("invalid number entered: \n");
						}
						else
						{
							strcpy(addressBook->contacts[real].phone,phone1);
						}
				
						break;
					case 3:

				 		
						printf("Enter tha email: ");
						scanf(" %[^\n]",email1);
						res = check_mail(email1);
						if(res == 0)
						{
							printf("invalid number entered: \n");
						}
						else
						{
							strcpy(addressBook->contacts[real].email,email1);
						}
				
						break;
					case 4:
						i=0;
					}
				}
}
void editContact(AddressBook *addressBook)
{
    int i=1;
    while(i)
    {
	   printf("1. Search By name\n2. Search by mobile\n3. Search By email\n4. Exit\n");
	   printf("Enter your choice: ");
	   int opt;
	   int opt1;
	   int edit_duplicate[10];
	   int count1=0;
	   char name[20];
	   char phone[20];
	   char email[20];
	   int res;
	   int real;
	   int flag=0;
	   scanf("%d",&opt);
	   switch(opt)
	   {
		   case 1:
			   printf("Enter name: ");
			   scanf(" %[^\n]",name);
			  real = search_name(addressBook,name,&count1); 
			  if(real != -1)
			  {
				  if(count1>1)
				  {
					  printf("\n******there are more than one contact with smae name***please re-type with phone or email***\n");
					  while(k)                                                                                                                                                    {                                                                                                                                                           printf("1. search by mobile\n2. search by email\n");                                                                                                        scanf("%d",&dup_opt);                                                                                                                                       if(dup_opt==1)                                                                                                                                              {                                                                                                                                                                   printf("Enter number: ");
						scanf(" %[^\n]",dup_num);
						for(int i=0;i<count1;i++)
						{
								dup_real = arr_dup[i];
								if(strcmp(addressBook->contacts[real].phone,dup_num)==0)
								{
									  flag3 =1;
									  break;
								}
						}
						if(flag3==1)
						{
							  edit_fun(addressBook,real);
							  k=0;
						}
						else
						{
								printf("\ninvalid number entered\n");
						}
				}
				}
				  }
				  else
				  {
					edit_fun(addressBook,real);	
				  }

			  }
			  else
			  {
				  printf("person not found: \n");
			  }
			   
			   break;
		   case 2:
			   printf("Enter phone: ");
			   scanf(" %[^\n]",phone);
			   real = search_phone(addressBook,phone); 
			   //int flag1 = search_phone(addressBook,phone)
			  if(real != -1)
			  {
		       		edit_fun(addressBook,real);		  
			  }
			  else
			  {
				  printf("person not found: \n");
			  }
			  break;
			   
		   case 3:
			   printf("Enter mail id: ");
			   scanf(" %[^\n]",email);
			   real = search_email(addressBook,email); 
			  if(real != 1)
			  {
				  edit_fun(addressBook,real);

			  }
			  else
			  {
				  printf("person not found: \n");
			  }
			   
		   case 4:
			   i=0;
			   break;
	   }
    }
}
void deleteContact(AddressBook *addressBook)
{
    int i=1;
    while(i)
    {
	    printf("1. Search By name\n2. Search by phone\n3. Search by email\n4. Exit");
	    int opt;
	    int res;
	    int real;
	    int flag=0;
	    char name[20];
	    char phone[20];
	    char email[20];
	    int dup[10];
	    int count=0;
	    printf("Enter your choice: ");
	    scanf("%d",&opt);
	    switch(opt)
	    {
		    case 1:
			    printf("Enter name: ");
			    scanf(" %[^\n]",name);
			    for(int i=0;i<addressBook->contactCount;i++)
			    {
				 int res = strcmp(addressBook->contacts[i].name,name);
				 if(res == 0)
				 {
					 flag =1;
					 dup[count] = i;
					 count++;
				 }
		           }

			    if(flag==0)
			    {
				    printf("contact not found\n");
			    }
			    else
			    {   
				if(count>=2)
				{
					for(int j=0;j<count;j++)
					{
						
						real = dup[j];
						printf("\n\n------------------------------------------\n");
						printf("%s\n%s\n%s\n",addressBook->contacts[real].name,addressBook->contacts[real].phone,addressBook->contacts[real].email);
						printf("\n-------------------------------------------\n");
					}
					printf("\n\n***your having more than one contact with same name**kindly check with mobile***\n\n");
				}
				else
				{	
			    	Contact temp = addressBook->contacts[real];
			    	addressBook->contacts[real] = addressBook->contacts[addressBook->contactCount-1];
			    	addressBook->contacts[addressBook->contactCount-1] = temp;
				(addressBook->contactCount--);
		
		
				}
			    }
			    break;
		    case 2:

			    printf("Enter phone: ");
			    scanf(" %[^\n]",phone); 
			    for(int i=0;i<(addressBook->contactCount);i++)
			    {
				 int res = strcmp(addressBook->contacts[i].phone,phone);
				 if(res == 0)
				 {
					 flag =1;
	 				 real =i;
					 break;
				 }
		           }
			    if(flag==0)
			    {
				    printf("invalid name entered: \n");
			    }
			    else
			    { 
			    	Contact temp = addressBook->contacts[real];
			    	addressBook->contacts[real] = addressBook->contacts[addressBook->contactCount-1];
			    	addressBook->contacts[addressBook->contactCount-1] = temp;
				(addressBook->contactCount--);
			    }
			    break;
		    case 3:
			    printf("Enter email id: ");
			    scanf(" %[^\n]",email);
			    
			    for(int i=0;i<(addressBook->contactCount);i++)
			    {
				 int res = strcmp(addressBook->contacts[i].email,email);
				 if(res == 0)
				 {
					 flag =1;
					 real =i;
					 break;
				 }
		           }
			    if(flag==0)
			    {
				    printf("invalid name entered: \n");
			    }
			    else
			    { 
			    	Contact temp = addressBook->contacts[real];
			    	addressBook->contacts[real] = addressBook->contacts[addressBook->contactCount-1];
			    	addressBook->contacts[addressBook->contactCount-1] = temp;
				(addressBook->contactCount--);
			    }
			    break;
		    case 4:
			    i=0;
			    break;
	    }
    }
}
