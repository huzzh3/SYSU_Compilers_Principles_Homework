#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include "global.h"

void getToken(char *filename);
TokenType checkIfReservedAndChange(char *tokenstring);
char *getTokenInStringFromTokenType(TokenType tokenType);

// DFA status
typedef enum {
         START_STATUS,
        ASSIGN_STATUS,
         EQUAL_STATUS,
       UNEQUAL_STATUS,
       COMMENT_STATUS,
        NUMBER_STATUS,
          REAL_STATUS,
        STRING_STATUS,
    IDENTIFIER_STATUS,
        FINISH_STATUS,
} DFAStatus;

#endif