#include <stdio.h>
#include "decode.h"
#include "types.h"
#include<string.h>
#include "common.h"
#include "encode.h"
#include<stdlib.h>
Status read_and_validate_decode_args(char *argv[], decodeInfo *decInfo)		//calling read_and_validate_decode_args function 
{
    if(strstr(argv[2],".bmp") != NULL)
    {
        decInfo->dest_image_fname = argv[2];				//checking if our argumen have .bmp or not
    }
    else
    {
        printf("FAIL: "".bmp"" file doesnot exits\n");
        printf("./lsb_steg: Decoding: ./lsb_steg -d <.bmp_file> [output file]\n");
        return e_failure;
    }
    if(argv[3]!= NULL)
    {
        decInfo->dup = strtok(argv[3],".");			//defining if user give the file or not if not as a programmer i am storing
    }
    else
    {
        decInfo->dup = "ashok";
    }
   return e_success;
}
Status open_file(decodeInfo *decInfo)				//calling open_file function
{
    decInfo->fptr_dest_image = fopen(decInfo->dest_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_dest_image == NULL)
    {
    	perror("fopen");					//if file doesnt open then i am throwing an error
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->dest_image_fname);

    	return e_failure;
    }
    return e_success;
}
Status decode_magic_string(decodeInfo *decInfo)		//defining decode_magic_string function 
{
    char magic[2];
    if(decode_data_from_image(magic, 2,decInfo->fptr_dest_image)==e_failure)
    {
        return e_failure;
    }
    //printf("magic_string encoded sucesfully\n");		//decoding magic string 
    strcpy(decInfo->magic_string,magic);
    printf("INFO: magic_string encoded sucesfully\n");
}
Status decode_byte_from_lsb(char* data, char *decode_buffer)		//defining decode_byte_from_lsb function
{
    int bit=0;
    for(int i=0;i<8;i++)
    {
        int res = decode_buffer[i] & 1;
        res = res <<i;						//getting a byte from lsb and storing in data
        bit = res | bit;
    }
    *data = bit;
}
Status decode_data_from_image(char *data, int size, FILE *fptr_dest_image)		//defing decode_data_from_image function
{
    char decode_buffer[8];
    for(int i=0;i<size;i++)
    {
        fread(decode_buffer,8,1,fptr_dest_image);
        decode_byte_from_lsb(&data[i], decode_buffer);			//reading 8 bytes from dest image and calling decode_byte_from_lsb
    }
}
Status decode_secret_file_extn_size(FILE *fptr_dest_image,decodeInfo *decInfo)		//defining decode_secret_file_extn_size function
{
    char extn_size_buffer[32];
    fread(extn_size_buffer,32,1,fptr_dest_image);
    int res =0;
    for(int i=0;i<32;i++)
    {
        int bit = extn_size_buffer[i] &1;
        bit = bit << i;						//reading a lsb from source and storing in buffer
        res = res | bit;
    }
    decInfo->ext_size = res;
    return e_success;
}
Status decode_secret_file_extn(FILE *fptr_dest_image, decodeInfo *decInfo)		//defining decode_secret_file_extn function
{
    char ext_b_data[decInfo->ext_size];
    decode_data_from_image(ext_b_data, decInfo->ext_size,fptr_dest_image);			//calling decode_data_from_image function and storing
    strcpy(decInfo->ext_data,ext_b_data);
    return e_success;
    
}
Status decode_secret_file_size(FILE *fptr_dest_image, decodeInfo *decInfo)		//calling decode_secret_file_size function
{
    char file_size_buffer[32];
    fread(file_size_buffer,32,1,fptr_dest_image);		//reading 32 bytes from dest image
    int res =0;
    for(int i=0;i<32;i++)
    {
        int bit = file_size_buffer[i] &1;
        bit = bit << i;						//getting a byte from lsb and storing
        res = res | bit;
    }
    decInfo->secret_fsize = res;
    return e_success;
}
Status decode_secret_file_data(decodeInfo *decInfo)		//defining decode_secret_file_dat function
{
    char secret_b_data[decInfo->secret_fsize];
    //printf("res ---> %u\n",decInfo->secret_fsize);
    decode_data_from_image(secret_b_data, decInfo->secret_fsize,decInfo->fptr_dest_image);
    fwrite(secret_b_data,decInfo->secret_fsize,1,decInfo->fptr_secret_data);		//writing data to the another .extn file
    return e_success;
}
Status do_decoding(decodeInfo *decInfo)		//defing do decoding function
{
    if(open_file(decInfo) == e_failure)			//calling open files function
    {
        printf("FAIL: file doesnt open\n");
        return e_failure;
    }
    printf("INFO: File opened succesfully\n");
    fseek(decInfo->fptr_dest_image,54,SEEK_SET);
    if(decode_magic_string(decInfo)==e_failure)	//calling decode_magic_string function
    {
        printf("FAIL: magic string doesnot encoded\n");
        return e_failure;
    }


    printf("INFO: Magic string encoded succesfuuly\n");
    char password[20];
    printf("Enter password to decode your data: ");
    scanf("%s",password);
    if(strcmp(decInfo->magic_string,password)!=0)
    {
        printf("ERROR: your password is wrong\n");
        return e_failure;
    }
    printf("INFO: password verification success: \n");


    if(decode_secret_file_extn_size(decInfo->fptr_dest_image,decInfo)==e_failure)		//calling decode_secret_file_extn_size function
    {
        printf("decoding size extendion not complted\n");
        return e_failure;
    }
    printf("INFO: decoding extension size success\n");


    if(decode_secret_file_extn(decInfo->fptr_dest_image,decInfo)==e_failure)		//calling decode_secret_file_extn data function
    {
        printf("INFO: extension data not decoded\n");
        return e_failure;
    }
    printf("INFO: extension data succesfull\n");


    decInfo->secret_file_name = malloc(strlen(decInfo->dup) + strlen(decInfo->ext_data) + 1);
    strcpy(decInfo->secret_file_name, decInfo->dup);
    strcat(decInfo->secret_file_name, decInfo->ext_data);
    
    if(decode_secret_file_size(decInfo->fptr_dest_image,decInfo)==e_failure)		//calling decode-secret_file_size function
    {
        printf("secret data is not encoded\n");
        return e_failure;
    }
    printf("INFO: secret size encoded success\n");


    decInfo->fptr_secret_data = fopen(decInfo->secret_file_name, "w");
    if (decInfo->fptr_dest_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->dest_image_fname);

    	return e_failure;
    }
    if(decode_secret_file_data(decInfo)==e_failure)		//calling decode_secret_file_data function
    {
        printf("secret filedata not encoded\n");
        return e_failure;
    }
    printf("INFO: Decoded succesfully\n");
    return e_success;

}
