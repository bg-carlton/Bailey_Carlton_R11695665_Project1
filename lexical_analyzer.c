/* Bailey Carlton (R11695665) | 3/17/2023

The lexemes and tokens of source code file that is given needs to be identified.

 This program takes a source file and gives a token vale to each lexeme for a parser to use. It reads the source file character by character to build lexemes.
 Lexemes of different characters are automatically delimited. Lexemes of the same character are delimited by space, tab, and next line characters,except if the
 lexeme is a special character/op lexeme. If that case, the lexeme's first character is compared to the second, then tokenized. The lexeme and its token are printed  */


#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define SPCHAR 2
#define UNKNOWN 99

/* Token Codes (for future parser)*/
#define ASSIGN_OP 10
#define LESSER_OP 11
#define GREATER_OP 12
#define EQUAL_OP 13
#define NEQUAL_OP 14
#define LEQUAL_OP 15
#define GEQUAL_OP 16
#define SEMICOLON 17
#define ADD_OP 18
#define SUB_OP 19
#define MULT_OP 20
#define DIV_OP 21
#define INC_OP 22
#define DEC_OP 23
#define LEFT_PAREN 24
#define RIGHT_PAREN 25
#define KEY_READ 26
#define KEY_WRITE 27
#define KEY_WHILE 28
#define KEY_DO 29
#define KEY_OD 30
#define IDENT 31
#define INT_LIT 32

/* Variables (from example)*/
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;
int nextToken;

/* Local Function declarations (from example)*/
static void addChar();
static void getChar();
static void getNonBlank();
int lex();



/* main function driver */
int main(int argc, char *argv[]){

    printf("DCooke Analyzer :: R11695665\n"); /* required for grading */

    /* open the file from the command line */
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open file \n");
    } else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }

    return 0;
}

/* keylookup -  a function to lookup keys and identifiers and return the token */
static int keylookup() {
    char readSt[5] = "read";
    char writeSt[6] = "write";
    char whileSt[6] = "while";
    char doSt[3] = "do";
    char odSt[3] = "od";

    if(strcmp(readSt, lexeme) == 0){
        printf("%s  KEY_READ\n", lexeme);
        nextToken = KEY_READ;
    }

    else if(strcmp(writeSt, lexeme) == 0){
        printf("%s KEY_WRITE\n", lexeme);
        nextToken = KEY_WRITE;
    }

    else if(strcmp(whileSt, lexeme) == 0){
        printf("%s KEY_WHILE\n", lexeme);
        nextToken = KEY_WHILE;
    }

    else if(strcmp(doSt, lexeme) == 0){
        printf("%s    KEY_DO\n", lexeme);
        nextToken = KEY_DO;
    }

    else if(strcmp(odSt, lexeme) == 0){
        printf("%s    KEY_OD\n", lexeme);
        nextToken = KEY_OD;
    }

    else{
        printf("%s     IDENT\n", lexeme);
        nextToken = IDENT;
    }

    return nextToken;
}

/* oplookup -  a function to lookup operators and parentheses and return the token */
static int oplookup() {
    switch (lexeme[0]) {
        /* if the first character of the lexeme has multiple possible tokens, determine based on the next character. Otherwise, search and return the token*/
        case ':':
            if(nextChar ==  '='){
                addChar();
                printf("%s    ASSIGN_OP\n", lexeme);
                nextToken = ASSIGN_OP;
                getChar();
            }
            else{
                printf("%s     UNKNOWN\n", lexeme);
                nextToken = UNKNOWN;
            }
            break;


        case '<':
            if(nextChar ==  '='){
                addChar();
                printf("%s    LEQUIAL_OP\n", lexeme);
                nextToken = LEQUAL_OP;
                getChar();
            }
            else{
                printf("%s     LESSER_OP\n", lexeme);
                nextToken = LESSER_OP;
            }
            break;


        case '>':
            if(nextChar ==  '='){
                addChar();
                printf("%s    GEQUAL_OP\n", lexeme);
                nextToken = GEQUAL_OP;
                getChar();
            }
            else{
                printf("%s     GREATER_OP\n", lexeme);
                nextToken = GREATER_OP;
            }
            break;


        case '=':
            printf("%s    EQUAL_OP\n", lexeme);
            nextToken = EQUAL_OP;
            break;


        case '!':
            if (nextChar == '='){
                addChar();
                printf("%s     NEQUAL_OP\n", lexeme);
                nextToken = NEQUAL_OP;
                getChar();
            }
            else{
                printf("%s     UNKNOWN\n", lexeme);
                nextToken = UNKNOWN;
            }
            break;


        case ';':
            printf("%s     SEMICOLON\n", lexeme);
            nextToken = SEMICOLON;
            break;


        case '+':
            if(nextChar ==  '+'){
                addChar();
                printf("%s    INC_OP\n", lexeme);
                nextToken = INC_OP;
                getChar();
            }
            else{
                printf("%s     ADD_OP\n", lexeme);
                nextToken = ADD_OP;
            }
            break;


        case '-':
            if(nextChar ==  '-'){
                addChar();
                printf("%s    DEC_OP\n", lexeme);
                nextToken = DEC_OP;
                getChar();
            }
            else{
                printf("%s     SUB_OP\n", lexeme);
                nextToken = SUB_OP;
            }
            break;


        case '*':
            printf("%s     MULT_OP\n", lexeme);
            nextToken = MULT_OP;
            break;


        case '/':
            printf("%s     DIV_OP\n", lexeme);
            nextToken = DIV_OP;
            break;


        case '(':
            printf("%s     LEFT_PAREN\n", lexeme);
            nextToken = LEFT_PAREN;
            break;


        case ')':
            printf("%s     RIGHT_PAREN\n", lexeme);
            nextToken = RIGHT_PAREN;
            break;


        default:
            printf("%s     UNKNOWN\n", lexeme);
            nextToken = UNKNOWN;
            break;
    } /* end of switch */
    return nextToken;
}


/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}


/* getChar - a function to get the next character of input and determine its character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {

        if (isalpha(nextChar)){
            charClass = LETTER;
        }

        else if (isdigit(nextChar)){
            charClass = DIGIT;
        }

        else{
            charClass = UNKNOWN;
        }
    }

    else {
        charClass = EOF;
    }
}


/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
static void getNonBlank() {
    while (isspace(nextChar)){
        getChar();
    }
}


/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers/keys */
        case LETTER:
            addChar();
            getChar();

            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }

            keylookup();
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            printf("%s     INT_LIT\n", lexeme);
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            addChar();
            getChar();
            oplookup();
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

    return nextToken;
} /* End of function lex */

