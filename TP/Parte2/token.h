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

    SEP,          // 15
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
