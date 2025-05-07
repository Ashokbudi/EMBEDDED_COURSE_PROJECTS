#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include<stdlib.h>
int num;
static int Bracket1=0; // for {}   Error Checking
static int Bracket2=0;  // for ()  Error Checking
static int Bracket3=0;  // for []  Error Checking
static int Double_quotation = 0;  // for " " Double_quotation Error Checking
static int Single_quotation;     // for ' '  Single_quotation Error Checking
static int count=0;

int Operator(char* str)
{
        
    static const char* specialCharacters[9] = {",",";","{","}","(",")","[","]","'",}; 
    for(int i=0;i<9;i++)
    {

        if(strstr(str,specialCharacters[i])!=NULL)
        {   //printf("SPECIAL CHARACTER IS %s\n",specialCharacters[i]);
            //printf("Str is %s",str);
            return 1;
        }
    }

    return 0;
}

Token getNextToken(char *filename,int temp,char*chh)
{   
 
    FILE *fptr = fopen(filename,"r");
    if(fptr==NULL)
    {
        printf("ERROR");
    }
    Token token;
    
  
    

    fseek(fptr,temp,SEEK_SET);
    char ch;
    char str[100];
    int i=0;
     
       
  while(1)
 {  
    ch = fgetc(fptr);

   if(ch=='\n')
   break;
    if(ch=='\n'||ch==' '||ch==EOF)                                 
    { 

      break;

    }  
  //printf("ch is %c\n",ch);
  str[i] = ch;                    // int main()
  i++;

} 
num = ftell(fptr);
//printf("num is %d\n",num);

char s[5];    //{',', ';', '{', '}', '(', ')', '[', ']', '\'','"'};
*chh= ch;
   // if(str[0]==';' || str[0]==',' || str[0]=='{' || str[0]=='}' || str[0]=='(' || str[0]==')' || str[0]=='[' || str[0]==']')
   if(ch=='\n')
   {
        str[i-1] = '\0';
    }else
    {
          str[i] ='\0';
    }     
    //str[i] = '\0';
   // printf("str is -> %s\n",str);
    int len = strlen(str);
  //  printf("Len is %d\n",len);
  //  printf("ch = %c\n",ch);
    fclose(fptr);
   
    strcpy(token.lexeme,str);
    
    token.type = isKeyword(str);

    return token;


 
}
void categorizeToken(Token* token)
{

}
int isKeyword(const char* str)
{    
  
    static const char* keywords[] = 
    {
        "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
        "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof",
         "struct","long","volatile","extern","enum","typedef","unsigned","auto","register",
         "union","bool","true","false","free","FILE","NULL","keyword"
    };
    

  
 // static const char* function[10] = {"main"};
    
        for(int i=0;*(keywords+i)!=NULL;i++)
    {
        if(strcmp(str,keywords[i])==0)
        {  
            
            return KEYWORD;
        
        }
       
    }
   
    
    
    
   
   return isOperator(str);
 
  
    


}
int isOperator(const char* str)
{  
   
    static const char* operators[] = {"+","-","*","/","%","=","!","<",">","|","&","++",
                                    "--","->","sizeof","<<",">>","<=",">=","==","!=","^","&&","||","?",":",
                                    "+=","-=","*=","=/","%=","&=","^=","|=","<<=",">>=","."};
    
    for(int i=0;operators[i]!=NULL;i++)
    {
        
        if(strcmp(str,operators[i])==0)
        {   
            return OPERATOR;
        }
    }
 
     return isSpecialCharacter(str);
}

int isSpecialCharacter(const char *str)
{
    
    
    
    static const char specialCharacters[10] ={',', ';', '{', '}', '(', ')', '[', ']', '\'','"'};// {",",";","{","}","(",")","[","]","'",};
    // static const char ptr[2] = {'"'}; 
    // if(strcmp(str,ptr)!=0)
    // {
    //     return SPECIAL_CHARACTER;
    // }
    for(int i=0;i<10;i++)
    {

        if(strchr(str,specialCharacters[i])!=NULL)
        {   //printf("SPECIAL CHARACTER IS %s\n",specialCharacters[i]);
            //printf("Str is %s",str);
            char ptr[] = "'"; 
            if(strstr(str,ptr)!=NULL)
            {
                Single_quotation++;
            }
            if(strchr(str,specialCharacters[9])!=NULL)
            {
                Double_quotation++;
            }
            if(specialCharacters[i]== '"'||specialCharacters[i]=='"')
            if(specialCharacters[i]== '{'||specialCharacters[i]=='}')
            {
                Bracket1++;
            }
            if(specialCharacters[i]== '('||specialCharacters[i]==')')
            {
                Bracket2++;
            }
            if(specialCharacters[i]== '['||specialCharacters[i]==']')
            {
                Bracket3++;
            }
            return SPECIAL_CHARACTER;
        }
    }

    return isFunction(str);
   
}
int isConstant(const char* str)
{
    static const char* constant[10] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
        static const char Hexa[2] = {'0','x'};
        for(int i=0;i<10;i++)
        {
            if(strstr(str,constant[i])!=NULL)
            {                  // int c = 0b1010;
                if(str[1]=='b')
                {
                    int i=2;
                    while(str[i]!='\0')
                    {
                        if(str[i]>='0'&&str[i]<='1')
                        {

                        }else
                        {
                            printf("\033[1;31m\nToken: %s Invalid Binary Number COMPILER ERROR:::\033[0m\n",str);
                            return UNKNOWN;
                        }
                        i++;
                    }
                }

                if(str[1]=='x')
                {
                    int Len = strlen(str);
                    if(str[Len-1]>='A'&&str[Len-1]<='F')
                    {
                      
                    }
                    else if(str[Len-1]>='a'&&str[Len-1]<='f')
                    {
                      
                    }else 
                    {
                        printf("\033[1;31m\nToken: %s Invalid HEXA Decimal Number Compiler Error:::\033[0m\n",str);
                        return UNKNOWN;
                    }
                
            

                }
                if(str[0]>='0'&&str[0]<='9')
                {
                    int Len = strlen(str);
                      
                        if(str[Len-1]!='f'&&str[Len-1]>='9')
                        {   
                            if(str[0]!='0'&&str[1]!='x'&&str[1]!='b')
                            {
                            if(Len>=2)
                            {
                            printf("\033[1;31m\nToken: %s Invalid floating Number Compiler Error:::\033[0m\n",str);
                            return UNKNOWN;
                            }
                        }
                
                    }//
                    
                }
                if(str[0]=='0'&&str[1]!='x')
                {
                    if(str[1]>='8')
                    {
                        if(str[1]!='b')
                        {
                        printf("\033[1;31m\nToken: %s Invalid Octal Number COMPILER ERROR:::\033[0m\n",str);
                        return UNKNOWN;
                        }
                    }
                }              // int a = 0b1010

                
                return CONSTANT;
            }
        }
    return isheaderfile(str);


}
int isheaderfile(const char* str)
{
    static const char* header = "#include";
    static const char* Macro = "#define";
    if(strstr(str,header)!=NULL)
    {
        return HEADER;
    }
    else if(strstr(str,Macro)!=0)
    {
        return MACRO;
    }
    return formate_specifier(str);
}
int formate_specifier(const char* str)
{
    static const char* formate_s = "%d";
    if(strcmp(str,formate_s)==0)
    {
        return FORMATE_SPECIFIER;
    }
    return String(str);
}
int String(const char* str)
{
    static const char* lowercase[25] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
        "l", "m", "o", "p", "q", "r", "s", "t", "u", "v",
        "w", "x", "y", "z"
    };

    static const char* uppercase[26] = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
        "W", "X", "Y", "Z"
    };
 
    if(str[0]=='%')
    return FORMATE_SPECIFIER;
   for(int i=0;i<25;i++)
   {
    if(strstr(str,lowercase[i])!=NULL)
    {
       //  printf("Num is %d",num);
         FILE*fptr = fopen("Source_File.txt","r");
         fseek(fptr,num,SEEK_SET);
         char ch = fgetc(fptr);
         //printf("ch = %c",ch);
         //printf(" ch = %c\n",ch);
         if(ch=='='||ch==','||ch==';'||ch=='['||ch==')')
         {
            return IDENTIFIER;
         }
         if(ch=='(')
         {
            fseek(fptr,num,SEEK_SET);
            fclose(fptr);
            return FUNCTION;
         }

         fseek(fptr,num-1,SEEK_SET);
         return STRING;
        
    }
   }
   for(int i=0;i<26;i++)
   {
    if(strstr(str,uppercase[i])!=NULL)
    {
        FILE*fptr = fopen("Source_File.txt","r");
         fseek(fptr,num,SEEK_SET);
         char ch = fgetc(fptr);
        // printf(" ch = %c\n",ch);
         if(ch=='(')
         {
            fseek(fptr,num,SEEK_SET);
            fclose(fptr);
            return FUNCTION;
         }
         if(ch=='='||ch==','||ch==';'||ch=='['||ch==')')
         {
            return IDENTIFIER;
         }
         fseek(fptr,num-1,SEEK_SET);
         return STRING;
    }
   }

   return Escape_Sequences(str);
}
int Escape_Sequences(const char* str)
{
static const char* escape_sequences[5] = {"\\n","\\r","\\t","\\a","\\v"};
    for(int i=0;i<5;i++)
    {

        if(strstr(str,escape_sequences[i])!=NULL)
        {   
           
            return ESCAPE_SEQUENCE;
        }
    }
    if(Bracket1%2!=0)
    {
        printf("\033[1;31m  { Bracket Missing Compiler ERROR:::: \033[0m\n\n");
    }
    if(Bracket2%2!=0)
    {
        printf("\033[1;31m  ) Bracket Missing Compiler ERROR:::: \033[0m\n\n");
    }
    if(Bracket3%2!=0)
    {
        printf("\033[1;31m  ] Bracket Missing Compiler ERROR:::: \033[0m\n\n");
    }
    if(Double_quotation%2!=0)
    {
        printf("\033[1;31m   Double Quotation Missing Compiler ERROR:::: \033[0m\n\n");
    }
    if(Single_quotation%2!=0)
    {
        printf("\033[1;31m   Single Quotation Missing Compiler ERROR:::: \033[0m\n\n");
    }
    //printf("%d",Double_quotation);
    return UNKNOWN;
}


int isIdentifier(const char* str)
{
    static const char* lowercase[26] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
        "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
        "w", "x", "y", "z"
    };

    static const char* uppercase[26] = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
        "W", "X", "Y", "Z"
    };
   for(int i=0;i<26;i++)
   {
    if(strcmp(str,lowercase[i])==0)
    {   
        
        return IDENTIFIER;

    }
   }

   for(int i=0;i<26;i++)
   {
    if(strcmp(str,uppercase[i])==0)
    {
        return IDENTIFIER;
    }
   }

   return isConstant(str);



}

int isFunction(const char* str)
{
    static const char* function[] = 
    {
            "printf",
            "scanf",
            "fopen",
            "fclose",
            "fread",
            "fwrite",
            "fgetc",
            "fputc",
            "fgets",
            "fputs",
            "feof",
            "ferror",
            "perror",
            "malloc",
            "calloc",
            "realloc",
            "free",
            "exit",
            "atoi",
            "atof",
            "strlen",
            "strcpy",
            "strncpy",
            "strcat",
            "strncat",
            "strcmp",
            "strncmp",
            "strchr",
            "strrchr",
            "qsort",
            "bsearch",
            "main",
    
    };
    for(int i=0;i<32;i++)
    {
    if(strcmp(str,function[i])==0)
    {   
        return FUNCTION;
    }
    }
  return   isIdentifier(str);
} 