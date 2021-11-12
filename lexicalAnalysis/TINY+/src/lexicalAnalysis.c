#include <stdio.h>
#include <ctype.h>
#include <string.h>


#include "lexicalAnalysis.h"

#define BUFFER_SIZE 255

char *getTokenInStringFromTokenTypeAndString(TokenType tokenType, char *str) {
    static char res[BUFFER_SIZE];
    
    if (tokenType >= IF && tokenType <= DOWNTO) {
        // It's reserved word
        sprintf(res, "(KEYWORD, %s)", str);
    }
    else if (tokenType >= SEMICOLON && tokenType <= RIGHT_PARENTHESIS) {
        // It's Single-character separator
        sprintf(res, "(SEP, %s)", tokenStringInSystem[tokenType]);
    }
    else if (tokenType >= PLUS && tokenType <= UNEQUAL) {
        // It's operator
        sprintf(res, "(OP, %s)", tokenStringInSystem[tokenType]);
    }
    else if (tokenType == IDENTIFIER) {
        // It's identifier
        sprintf(res, "(ID, %s)", str);
    }
    else if (tokenType == NUMBER) {
        // It's number
        sprintf(res, "(NUM, %s)", str);
    }
    else if (tokenType == STRING) {
        // It's string
        sprintf(res, "(STRING, %s)", str);
    }

    return res;
}

TokenType checkIfReservedAndChange(char *tokenstring) {
    for (size_t i = 0; i < REVERSE_WORDS_NUM; i++) {
        if (!strcmp(tokenstring, reversedWords[i].str)) {
            return reversedWords[i].tokenType;
        }
    }
    return IDENTIFIER;
}

void getToken(char *filename) {
    // Necessary variables to read/write file
    FILE *fp;
    FILE *fpWrite;
    char buffer[BUFFER_SIZE];
    char tokenSaveFilepath[BUFFER_SIZE] = ".\\bin\\token.txt";

    // Necessary variables to handle token
    int tokenStringIndex = 0;      // Record the location of the character
    char tokenString[BUFFER_SIZE]; // Record the token string
    TokenType currentTokenType;    // Record current token type
    DFAStatus currentStatus;       // Record current DFA status
    BOOL needToBeSaved;            // Record the character if needed to be saved

    // Read the file
    if ((fp = fopen(filename, "rb+")) == NULL) {
        printf("\nCannot open file: %s!", filename);
        return;
    }
    else if ((fpWrite = fopen(tokenSaveFilepath, "w+")) == NULL) {
        // printf("\nCannot open file: %s!", tokenSaveFilepath);

        // Create a token.txt in this directory
        if ((fpWrite = fopen(".\\token.txt", "w+")) == NULL) {
            printf("\nCannot open file: %s!", ".\\token.txt");
            return;
        }
    }

    // Initial the currentStatus to start
    currentStatus = START_STATUS;
    // Read the string to buffer and make sure current state is valid
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL && currentStatus != FINISH_STATUS) {
        // Necessary variable to read character
        size_t bufferLength       = strlen(buffer);
        size_t currentBufferIndex = 0;
        char   currentCharacter;

        // Ensure you can get the character and current state is valid
        while (currentBufferIndex < bufferLength && currentStatus != FINISH_STATUS) {
            // Get current character
            currentCharacter = buffer[currentBufferIndex];
            // Set the character need to be save
            needToBeSaved = TRUE;

            // Switch to another status
            switch (currentStatus)
            {
            case START_STATUS:
                if (isdigit(currentCharacter)) {
                    currentStatus = NUMBER_STATUS;
                }
                else if (isalpha(currentCharacter)) {
                    currentStatus = IDENTIFIER_STATUS;
                }
                else if (currentCharacter == '"') {
                    needToBeSaved = FALSE;
                    currentStatus = STRING_STATUS;
                }
                else if (currentCharacter == ':') {
                    currentStatus = ASSIGN_STATUS;
                }
                else if (currentCharacter == '=') {
                    currentStatus = EQUAL_STATUS;
                }
                else if (currentCharacter == '!') {
                    currentStatus = UNEQUAL_STATUS;
                }
                else if (currentCharacter == ' ' || currentCharacter == '\t' || currentCharacter == '\n' || currentCharacter == '\r') {
                    // You need to ignore white space
                    needToBeSaved = FALSE;
                    currentStatus = START_STATUS;
                }
                else if (currentCharacter == '/') {
                    // You need to check the comment
                    if (buffer[currentBufferIndex + 1] == '*') {
                        needToBeSaved = FALSE;
                        currentStatus = COMMENT_STATUS;
                    }
                }
                else {
                    // There're Single-character operators
                    // Change the state to finish first
                    currentStatus = FINISH_STATUS;

                    // Check the operator
                    switch (currentCharacter)
                    {
                    case '+':
                        currentTokenType = PLUS;
                        break;
                    case '-':
                        currentTokenType = MINUS;
                        break;
                    case '*':
                        currentTokenType = TIME;
                        break;
                    case '/':
                        currentTokenType = DIVIDE;
                        break;
                    case '%':
                        currentTokenType = MODULO;
                        break;
                    case '<':
                        currentTokenType = LESS_THAN;
                        break;
                    case '>':
                        currentTokenType = GREATER_THAN;
                        break;
                    case ',':
                        currentTokenType = COMMA;
                        break;
                    case ';':
                        currentTokenType = SEMICOLON;
                        break;
                    case '(':
                        currentTokenType = LEFT_PARENTHESIS;
                        break;
                    case ')':
                        currentTokenType = RIGHT_PARENTHESIS;
                        break;
                    default:
                        currentTokenType = ERROR;
                        printf("default error\n");
                        break;
                    }
                }
                break;
            case ASSIGN_STATUS:
                // It must be done, for there's only ':='
                currentStatus = FINISH_STATUS;
                if (currentCharacter == '=') {
                    currentTokenType = ASSIGN;
                }
                else {
                    // It must be error
                    currentBufferIndex--;
                    needToBeSaved = FALSE;
                    currentTokenType = ERROR;
                }
                break;

            case EQUAL_STATUS:
                // It must be done, for there's only '=='
                currentStatus = FINISH_STATUS;
                if (currentCharacter == '=') {
                    currentTokenType = EQUAL;
                }
                else {
                    // It must be error
                    currentBufferIndex--;
                    needToBeSaved = FALSE;
                    currentTokenType = ERROR;
                }
                break;

            case UNEQUAL_STATUS:
                // It must be done, for there's only '!='
                currentStatus = FINISH_STATUS;
                if (currentCharacter == '=') {
                    currentTokenType = UNEQUAL;
                }
                else {
                    // It must be error
                    currentBufferIndex--;
                    needToBeSaved = FALSE;
                    currentTokenType = ERROR;
                }
                break;

            case COMMENT_STATUS:
                // You need to ignore comment to its end
                needToBeSaved = FALSE;
                if (currentCharacter == '/') {
                    // the comment is end
                    currentStatus = START_STATUS;
                }
                break;

            case IDENTIFIER_STATUS:
                if (!isalpha(currentCharacter) && !isdigit(currentCharacter)) {
                    // the identifier is done
                    currentBufferIndex--;       // get back
                    needToBeSaved = FALSE;
                    currentStatus = FINISH_STATUS;
                    currentTokenType  = IDENTIFIER;
                }
                else if (currentBufferIndex == strlen(buffer) - 1) {
                    // The end of line/file
                    needToBeSaved = TRUE;
                    currentStatus = FINISH_STATUS;
                    currentTokenType  = IDENTIFIER;
                }
                break;

            case NUMBER_STATUS:
                if (!isdigit(currentCharacter)) {
                    if (currentCharacter == '.') {
                        currentStatus = REAL_STATUS;
                    }
                    else {
                        currentBufferIndex--;
                        needToBeSaved = FALSE;
                        currentStatus = FINISH_STATUS;
                        currentTokenType  = NUMBER;
                    }
                }
                break;
            
            case REAL_STATUS:
                if (!isdigit(currentCharacter)) {
                    currentBufferIndex--;
                    needToBeSaved = FALSE;
                    currentStatus = FINISH_STATUS;
                    currentTokenType  = NUMBER;
                }
                break;

            case STRING_STATUS:
                needToBeSaved = TRUE;
                if (currentCharacter == '"') {
                    // The string is done
                    needToBeSaved = FALSE;
                    currentStatus = FINISH_STATUS;
                    currentTokenType  = STRING;
                }
                break;

            case FINISH_STATUS:
                break;

            default:
                // There might something wrong
                currentStatus = FINISH_STATUS;
                currentTokenType = ERROR;
                break;
            }

            if (needToBeSaved == TRUE && tokenStringIndex < BUFFER_SIZE) {
                // Record the string
                tokenString[tokenStringIndex++] = currentCharacter;
            }

            if (currentStatus == FINISH_STATUS) {
                if (currentTokenType == ERROR) {
                    fprintf(fpWrite, "error with \' %s \'\n", tokenString);
                    
                    fclose(fp);
                    fclose(fpWrite);

                    return;
                }
                else {
                    if (currentTokenType == IDENTIFIER) {
                        currentTokenType = checkIfReservedAndChange(tokenString);
                    }

                    char *tokenInString = getTokenInStringFromTokenTypeAndString(currentTokenType, tokenString);

                    // Save the token in file
                    fprintf(fpWrite, "%s\n",tokenInString);
                    
                    // Reset
                    tokenStringIndex = 0;
                    memset(tokenString, 0, sizeof(tokenString));

                    // Begin next analysis
                    currentStatus = START_STATUS;       // restart
                }
            }

            // increase the currentBufferIndex to ensure you can read next character
            currentBufferIndex++;
        }
    }
    fclose(fp);
    fclose(fpWrite);
}