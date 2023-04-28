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
    OP_AND,       // 4
    OP_LT,        // 5
    OP_GT,        // 6
    OP_ADD,       // 7
    OP_SUB,       // 8
    OP_MUL,       // 9
    OP_DIV,       // 10
    OP_ASSIGN,    // 11
    OP_EQUAL,     // 12
    OP_NOT_EQUAL, // 13
    OP_NOT,       // 14

    SEP,          // 15
    SEP_LPAREN,   // 16
    SEP_RPAREN,   // 17
    SEP_LCOLCH,   // 18
    SEP_RCOLCH,   // 19
    SEP_LCHAVE,   // 20
    SEP_RCHAVE,   // 21
    SEP_PONTVIR,  // 22
    SEP_PONTO,    // 23
    SEP_VIRGULA,  // 24

    COMMENT,     //  25

    END_OF_FILE   // 26
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
