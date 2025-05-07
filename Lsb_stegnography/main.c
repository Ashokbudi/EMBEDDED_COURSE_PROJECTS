/*	***DOCUMENTATION**
   
   NAME: BUDI ASHOK KUMAR
   DATE: 10-04-2025
   DESCRIPTION: IT IS AN LSB-STEGNOGRAPHY PROJECT IN WHICH IN ENCODES A SECRET DATA INTO A .BMP FILE AND DECODES IT WITH A MAGIC STRING
*/
#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "decode.h"
OperationType check_operation_type(char *);
int main(int argc,char* argv[])
{
	if(argc >= 3)                                       //checking the arguments count
	{
	if(check_operation_type(argv[1]) == e_encode)
	{
		EncodeInfo encInfo;				//declaring a structure variable
		if(argc ==4 || argc ==5)
		{
			printf("you selected encoding option\n");
			if(read_and_validate_encode_args(argv,&encInfo) == e_failure)	//calling read_and_validata_args functions
			{
				printf("your files are not appropriate to encode\n");
				return 0;
			}
			if(do_encoding(&encInfo) == e_failure)		//calling de_encoding function
			{
				printf("your encoding not succesfully completed\n");
				return e_failure;
			}
			printf("INFO: ##ENCODING SUCCESSFULLY COMPLETED##\n");
			fclose(encInfo.fptr_src_image);
			fclose(encInfo.fptr_stego_image);		//after that i am closing all file pointers
			fclose(encInfo.fptr_secret);
			printf("\a");
		}
		else{
			printf("ERROR: Enter valid arguments to encode\n");
		}
	
	}
	else if(check_operation_type(argv[1]) == e_decode)	
	{
		decodeInfo decInfo;			//declaring a structure variable for decoding
		printf("you selected decoding option\n");
		if(read_and_validate_decode_args(argv,&decInfo) == e_failure)		//calling read_and validate_args function
		{
			printf("Decode not completed\n");
			return e_failure;
		}
		if(do_decoding(&decInfo) == e_failure)				//calling do_decoding function
		{
			printf("decoding not yet complted\n");
			return e_failure;
		}
		printf("INFO: ## DECODING SUCCESSFULLY COMPLETED ##\n");
		printf("\a");
	}
	else
	{
		printf("ERROR: Enter a valid operation type to do\n");
	}

	return 0;
	}
	else{
		printf("Enter -e for encoding or -d for decoding\n");
		printf("Enter valid arguments");
	}

}
OperationType check_operation_type(char *symbol)		//checking operation type function
{
	if(strcmp(symbol,"-e") == 0)
	{
		return e_encode;			//if user enters -e then it return e_encode
	}
	else if(strcmp(symbol,"-d") == 0)
	{
		return e_decode;			//if user enters -d then it returns e_decode
	}
	else
	{
		return e_unsupported;			//if user enters either not -e or -d the it return e_unsupported
	}
}
