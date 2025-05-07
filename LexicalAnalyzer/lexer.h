#ifndef LEXER_H
#define LEXER_H
#define MAX_KEYWORDS 21
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    FUNCTION,
    IDENTIFIER,
    HEADER,
    FORMATE_SPECIFIER,
    STRING,
    ESCAPE_SEQUENCE,
    MACRO,
    UNKNOWN

} TokenType;
typedef struct
{
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

void initializeLexer(const char* filename);
Token getNextToken(char *filename,int,char*); // FIXED

//Token getNextToken();
int Operator(char*);
int Escape_Sequences(const char* str);
int String(const char* str);
void categorizeToken(Token* token);
int formate_specifier(const char* str);
int isKeyword(const char* str);
int isheaderfile(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(const char* ch);
int isConstant(const char* str);
int isFunction(const char* str);
int error_check(char* file);
int isIdentifier(const char* str);

#endif
