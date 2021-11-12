#ifndef GLOBAL_H
#define GLOBAL_H

#define BUFFER_SIZE 255

// Bool
typedef int BOOL;
#define TRUE 1
#define FALSE 0

// Token type
typedef enum {
    // Keywords
    IF, ELSE, WRITE, READ, RETURN, BEGIN, END, MAIN, INT, REAL, WHILE, DO, FOR, UPTO, DOWNTO,

    // Single-character separators
    SEMICOLON, COMMA, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,

    // Single-character operators
    PLUS, MINUS, TIME, DIVIDE, MODULO, GREATER_THAN, LESS_THAN,

    // Multi-character operators
    ASSIGN, EQUAL, UNEQUAL,

    // Identifier, Number and String
    IDENTIFIER, NUMBER, STRING,

    // Other
    ERROR, ENDFILE
} TokenType;

// Token (Token type and str) 
typedef struct token {
    char *str;
    TokenType tokenType;
} token;


#define REVERSE_WORDS_NUM 15

// Some global array
extern token reversedWords[];
extern char tokenStringInSystem[][BUFFER_SIZE];

#endif