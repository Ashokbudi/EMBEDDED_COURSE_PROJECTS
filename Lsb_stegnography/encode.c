#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "common.h"
#include<unistd.h>
/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)            //this function is for finding size of our source image
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);                  //getting width of the image
    printf("INFO: width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);                //getting height of the image
    printf("INFO: height = %u\n", height);
    rewind(fptr_image);

    // Return image capacity
    return width * height * 3;
}
uint get_file_size(FILE *fptr)
{
                                               //find the size of secret file data and return it to check_capacity function ///long size_secret_file;
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
                                                                                     //opening Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
                                                                                     // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

                                                                                    //opening Secret file 
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
                                                                                  // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

                                                                               //opening Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
                                                                              // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
    	return e_failure;
    }

                                                                           // No failure return e_success
    return e_success;
}
Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity =  get_image_size_for_bmp(encInfo->fptr_src_image);        // call get_image_size_for_bmp function
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);                   //call get_file_size function
    uint header_bits = 54;
    uint magic_len = strlen(MAGIC_STRING);                                               //checking magic string length
    uint magic = magic_len*8;
    rewind(encInfo->fptr_secret); 
    if(encInfo->image_capacity <(header_bits + 32 + magic + 32 + encInfo->size_secret_file + 32 + 32))        //checking the image capacity with secret file
    {
        return e_failure;
    }
    return e_success;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    int flag=0;
    if((argv[2][0]>='a' && argv[2][0] <='z') ||(argv[2][0]>='A' && argv[2][0] <='Z'))
    {
        flag=1;                                                                       //checking source file is .bmp or not
    }
    if(strstr(argv[2],".bmp") != NULL && flag==1)
    {
        encInfo->src_image_fname = argv[2];
        printf("INFO: Opened SkeletonCode/beautiful.bmp\n");  
    }
    else
    {
        printf("FAIL: "".bmp"" file doesnot exits\n");
        printf("./lsb_steg: Encoding: ./lsb_steg -e <.bmp_file> <.text_file> [output file]\n");
        return e_failure;
    }
    if(strstr(argv[3],".txt") != NULL || strstr(argv[3],".c") != NULL || strstr(argv[3],".sh") != NULL)
    {
        encInfo->secret_fname = argv[3];                                             //checing secret file extension
        printf("INFO: opened %s\n",encInfo->secret_fname); 
    }
    else
    {
        printf("FAIL: ""extension failure"" file doesnot exits\n");
        return e_failure;
    }
    if(argv[4] == NULL)
    {
        encInfo->stego_image_fname = "ashok.bmp";                 //checking if source image is not there so as a programmer i will craete a file
    }
    else
    {
        flag=0;
        if((argv[4][0]>='a' && argv[4][0] <='z') ||(argv[4][0]>='A' && argv[4][0] <='Z'))
        {
            flag=1;
        }
        if(strstr(argv[4],".bmp") != NULL && flag==1)
        {
            encInfo->stego_image_fname = argv[4];                    //checking destination image file
            printf("INFO: opened %s\n",encInfo->stego_image_fname);
        }
        else
        {
            printf("FAIL: "".bmp"" file doesnot exits\n");
            printf("./lsb_steg: Encoding: ./lsb_steg -e <.bmp_file> <.text_file> [output file]\n");
            return e_failure;
        }
    }
    return e_success;
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    rewind(fptr_src_image);
    char buffer[54];
    fread(buffer,54,1,fptr_src_image);              //reading 54 bytes from source
    fwrite(buffer,54,1,fptr_dest_image);            //writing 54 bytes to destination
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char magic_str[]=MAGIC_STRING;
    int size = strlen(magic_str);               //step1: int size find size of magic string
    if(encode_data_to_image(magic_str,size, encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_failure)     //call encode_data_to_image(magic_string,size, encInfo->fptr_src_image, encinfo->fptr_stego_image)
    {
        return e_failure;
    }
    return e_success;
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    int bit_get;
    for(int i=0;i<8;i++)
    {
        bit_get = data & (1<<i);                    //getting a lsb from data
        bit_get = bit_get >> i;                     //shifting in times to left
        image_buffer[i] = image_buffer[i] & (~(1));   //clearing lsb in buffer[i]
        image_buffer[i] = image_buffer[i] | bit_get;    //or with buffer[i] with bit_get
    }
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char image_buffer[8];
    for(int i=0;i<size;i++)
    {
        fread(image_buffer,8,1,fptr_src_image);         //reading 8 bytes from src image
        encode_byte_to_lsb(data[i],image_buffer);       //calling encode_byte_to_lsb
        fwrite(image_buffer,8,1,fptr_stego_image);      //writing 8 bytes to dest image
    }
    return e_success;
    //char image_buffer[8];
    //step1: read 8 bytes from the src image store into imagebuffer
    //step 2: call the encode_byte_to _lsb(data[i],imagebuffer)
    //step 3: write the imageBuffer to dest image
    //step 4: repeat the same process
    //step 5: return e_success
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    rewind(encInfo->fptr_secret);
    char ext[1];
    for(int i=0;i<32;i++)
    {
        fread(ext,1,1,encInfo->fptr_src_image);
        ext[0] = ext[0] & (~1);     
        int bit_g = file_size & (1<<i);
        bit_g = bit_g >> i;                                  //getting a lsb from size and replcing into ext buffer
        ext[0] = ext[0] | bit_g;
        fwrite(ext,1,1,encInfo->fptr_stego_image);
    }
    return e_success;

}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    uint len = strlen(file_extn);
    char ext[1];
    for(int i=0;i<32;i++)
    {
        fread(ext,1,1,encInfo->fptr_src_image);
        ext[0] = ext[0] & (~1);                                 //getting a lsb from size and replcing into ext buffer
        int bit_g = len & (1<<i);                       
        bit_g = bit_g >> i;
        ext[0] = ext[0] | bit_g;
        fwrite(ext,1,1,encInfo->fptr_stego_image);
    }
    char img_buffer[8];
    for(int i=0;i<len;i++)
    {
        fread(img_buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i],img_buffer);            //encoding extn data to dest image
        fwrite(img_buffer,8,1,encInfo->fptr_stego_image);
    }
    return e_success;
    
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char sec_buffer[encInfo->size_secret_file];
    fread(sec_buffer,encInfo->size_secret_file,1,encInfo->fptr_secret);
    if(encode_data_to_image(sec_buffer,encInfo->size_secret_file,encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)
    {
        return e_failure;               //encoding secret file data
    }
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch[1];
    
    while(fread(ch,1,1,fptr_src) > 0)
    {
        fwrite(ch,1,1,fptr_dest);               //encoding remaining data
    }
    return e_success;
}
Status do_encoding(EncodeInfo *encInfo)
{                                                       //calling decoding function
    sleep(1);
	if(open_files(encInfo) == e_failure)
    {
        printf("FAIL: Opening files");                  //opening all files
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("INFO: checking capacity of file\n");
    sleep(1);
    if(check_capacity(encInfo)==e_failure)          //calling check capacity function
    {
        printf("FAIL: check capacity failure\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("INFO: copying BMP header\n");
    sleep(1);
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)!=e_success)   //calling copy_bmp_header function
    {
        printf("FAIL: failed to copy 54 bytes");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("encoding magic string\n");
    sleep(1);
    if(encode_magic_string(MAGIC_STRING,encInfo)==e_failure)            //calling encode_magic string function
    {
        printf("encoding magic string error\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("INFO: Secret File Extension size encoding\n");
    sleep(1);
    char* str = strchr(encInfo->secret_fname,'.');
    strcpy(encInfo->extn_secret_file,str);
    printf("INFO: SecretFile extension data encoding\n");
    if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_failure)   //calling encode_secret_file_extn function
    {
        printf("FAIL: Extension not encoded\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    sleep(1);
    printf("INFO: secret file data size encoding\n");
    if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_failure)   //calling encode_secret_file_size function
    {
        printf("FAIL: secret file not encoded\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("INFo: secret file data encoding\n");
    sleep(1);
    if(encode_secret_file_data(encInfo)==e_failure)                 //calling encode_secret_file_data function
    {
        printf("FAIL: secret data not encoded succesfiully\n");
        return e_failure;
    }
    printf("INFO: DONE\n");
    printf("INFo: remaining data encoding: \n");
    sleep(1);
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_failure)  //calling copy_remaining_img_data function
    {
        return e_failure;
    }
    printf("INFO: Data encoding succesfully completed\n");
    //step 5 call the encode_magic_string(MAGIC_STRING,encInfo)-->true print succes message go to step 6
    //false -----> return e_failure
    //step 6: Extract .txt fromthe secret file name
    //and store into the structure member (extn_secret_file)
    return e_success;

}
