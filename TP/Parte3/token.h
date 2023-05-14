#include <iostream>
#include <ctype.h> //Funções de caracteres
#include <string>

using namespace std;

enum Names
{
    UNDEF, // 0

    ID, // 1

    INTEGER_LITERAL, // 2

    OP,           // 3
    AND,       // 4
    LT,        // 5
    GT,        // 6
    ADD,       // 7
    SUB,       // 8
    MUL,       // 9
    DIV,       // 10
    ASSIGN,    // 11
    EQUAL,     // 12
    NOT_EQUAL, // 13
    NOT,       // 14

    SEP,      // 15
    LPAREN,   // 16
    RPAREN,   // 17
    LCOLCH,   // 18
    RCOLCH,   // 19
    LCHAVE,   // 20
    RCHAVE,   // 21
    PONTVIR,  // 22
    PONTO,    // 23
    VIRGULA,  // 24

    COMMENT,     //  25

    END_OF_FILE,   // 26

    BOOLEAN, // 27
    CLASS,  // 28
    ELSE,   // 29
    EXTENDS, // 30
    FALSE, // 31
    IF, // 32
    INT, // 33
    LENGTH, // 34
    MAIN, // 35
    NEW, // 36
    PUBLIC, // 37
    RETURN, // 38
    STATIC, // 39
    STRING, // 40
    SYSTEM, // 41
    OUT, // 42
    PRINTLN, // 43
    THIS, // 44
    TRUE, // 45
    VOID, // 46
    WHILE // 47
};

class Token
{
public:
    int name;
    int attribute;
    string lexeme;

    Token(int name)
    {
        this->name = name;
        attribute = UNDEF;
    }

    Token(int name, string l)
    {
        this->name = name;
        attribute = UNDEF;
        lexeme = l;
    }

    Token(int name, int attr)
    {
        this->name = name;
        attribute = attr;
    }
};
