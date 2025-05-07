#include <stdio.h>
#include "lexer.h"
#include<string.h>
extern int num;
int main(int argc, char *argv[]) 

{

   
    
    Token token;
    char ptr[100];
    char *p;
    int temp=num;
    char ch;
    if(error_check(argv[1])!=1)
    {
      printf("Error occured\n");
      return 0;
    }
    while ((token = getNextToken(argv[1],temp,&ch)).type != UNKNOWN)
     {   
         if(token.type==KEYWORD)
         {
             p = "KEYWORD";
         }
         else if(token.type==OPERATOR)
         {
            p = "OPERATOR";
         }else if(token.type==SPECIAL_CHARACTER)
         {
            p = "SPECIAL_CHARACTER";
         }
         else if(token.type==FUNCTION)
         {
            p = "FUNCTION";
         }
         else if(token.type==IDENTIFIER)
         {
           p = "IDENTIFIER (VARIABLE)";
         }
         else if(token.type==CONSTANT)
         {
            p = "CONSTANT";
         }
         else if(token.type==HEADER)
         {
            p = "HEADER";
         }
         else if(token.type==FORMATE_SPECIFIER)
         {
            p = "FORMATE SPECIFIER";
         }
         else if(token.type==STRING)
         {

            p = "STRING";
         }
         else if(token.type==ESCAPE_SEQUENCE)
         {
            p = "ESCAPE SEQUENCE";
         }
         else if(token.type==MACRO)
         {
            p = "MACRO";
         }

        printf("Token: %s  ->  Type: %s\n\n", token.lexeme,p);
      //   if(token.type==FUNCTION)
      //   {      
      //       strcpy(token.lexeme,"(");
      //       p = "SPECIAL_CHARACTER";
      //       printf("Token: %s  ->  Type: %s\n\n", token.lexeme,p);
          
      //   }
        
        //break;
        if(ch==' ')
        {
           temp =num;
       // temp = num+1;
        }else temp = num;
        //printf("ch is %c\n",ch);
    }
    if(token.type==UNKNOWN)
    {
      printf("\033[1;31m:::COMPILATION DONE:::\033[0m\n");

    }
    printf("\033[1;33mFILE POINTER IS -> %d\033[0m\n", num);

    return 0;
}
