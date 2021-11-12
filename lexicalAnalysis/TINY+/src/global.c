#include "global.h"

// Reversed words
token reversedWords[] = {
    {"IF", IF},
    {"ELSE", ELSE},
    {"WHILE", WHILE},
    {"DO", DO},
    {"FOR", FOR},
    {"UPTO", UPTO},
    {"DOWNTO", DOWNTO},
    {"READ", READ},
    {"WRITE", WRITE},
    {"BEGIN", BEGIN},
    {"END", END},
    {"MAIN", MAIN},
    {"RETURN", RETURN},
    {"INT", INT},
    {"REAL", REAL}
};

// Array stores token string
char tokenStringInSystem[][BUFFER_SIZE] = {
    // Keywords
    "IF", "ELSE", "WRITE", "READ", "RETURN", "BEGIN", "END", "MAIN", "INT", "REAL", "WHILE", "DO", "FOR", "UPTO", "DOWNTO",

    // Single-character separators
    ";", ",", "(", ")",

    // Single-character operators
    "+", "-", "*", "/", "%", ">", "<",

    // Multi-character operators
    ":=", "==", "!=",

    // Identifier", "Number and String
    "IDENTIFIER", "NUMBER", "STRING",

    // Other
    "ERROR", "ENDFILE"
};