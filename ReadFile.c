#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
char line[];
int lexLen;
int token;
int nextToken;
FILE *textFile;

/* Function declarations */
void addChar();
void getLine();
void getChar(char line[]);
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int main() {
    /* Open the input data file and process its contents */
    if ((textFile = fopen("front.in", "r")) == NULL) {
        printf("ERROR - cannot open front.in \n");
    }
    else {
        getChar(line);
        do {
            lex();
        } while (nextToken != EOF);
    }
}

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken; }

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else {
        printf("Error - lexeme is too long \n");
    }
}

void getLine() {
    while (textFile != EOF) {
        
    }
    fclose(textFile);
}

void getChar(char line[]) {
    if ((nextChar = getc(textFile)) != EOF) {
        if (isalpha(nextChar)) {
            charClass = LETTER;
        }
        else if (isdigit(nextChar)) {
            charClass = DIGIT;
        }
        else charClass = UNKNOWN;
    }
    else charClass = EOF;
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar(line);
}

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    /* Parse identifiers */
        case LETTER:
            addChar();
            getChar(line);
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar(line);
            }
            nextToken = IDENT;
            break;
    /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar(line);
            while (charClass == DIGIT) {
                addChar();
                getChar(line);
            }
            nextToken = INT_LIT;
            break;
    /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar(line);
            break;
    /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}  /* End of function lex */

