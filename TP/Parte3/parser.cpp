#include "parser.h"

Parser::Parser(string input)
{
    currentST = globalST = new SymbolTable();
    initSimbolTable();

    scanner = new Scanner(input, globalST);
}

void Parser::advance()
{
    lToken = scanner->nextToken();
}

void Parser::match(int t)
{
    if (lToken->name == t || lToken->attribute == t)
        advance();
    else
        error("Erro inesperado");
}

void Parser::run()
{
    advance();

    program();

    cout << "Compilação encerrada com sucesso!\n";
}
// .1 Program -> MainClass (ClassDeclaration) * EOF
void Parser::program()
{
    if (lToken->name == CLASS)
        classList();
}

void Parser::classList()
{
    do
    {
        classDeclaration();
    } while (lToken->name == CLASS);
}

void Parser::initSimbolTable()
{
    Token *t;

    t = new Token(BOOLEAN, "boolean");
    globalST->add(new STEntry(t, "boolean"));
    t = new Token(CLASS, "class");
    globalST->add(new STEntry(t, "class"));
    t = new Token(ELSE, "else");
    globalST->add(new STEntry(t, "else"));
    t = new Token(EXTENDS, "extends");
    globalST->add(new STEntry(t, "extends"));
    t = new Token(FALSE, "false");
    globalST->add(new STEntry(t, "false"));
    t = new Token(IF, "if");
    globalST->add(new STEntry(t, "if"));
    t = new Token(INT, "int");
    globalST->add(new STEntry(t, "int"));
    t = new Token(LENGTH, "length");
    globalST->add(new STEntry(t, "length"));
    t = new Token(MAIN, "main");
    globalST->add(new STEntry(t, "main"));
    t = new Token(PUBLIC, "public");
    globalST->add(new STEntry(t, "public"));
    t = new Token(RETURN, "return");
    globalST->add(new STEntry(t, "return"));
    t = new Token(STATIC, "static");
    globalST->add(new STEntry(t, "static"));
    t = new Token(STRING, "String");
    globalST->add(new STEntry(t, "String"));
    t = new Token(SYSTEM, "System");
    globalST->add(new STEntry(t, "System"));
    t = new Token(OUT, "out");
    globalST->add(new STEntry(t, "out"));
    t = new Token(PRINTLN, "println");
    globalST->add(new STEntry(t, "println"));
    t = new Token(THIS, "this");
    globalST->add(new STEntry(t, "this"));
    t = new Token(TRUE, "true");
    globalST->add(new STEntry(t, "true"));
    t = new Token(VOID, "void");
    globalST->add(new STEntry(t, "void"));
    t = new Token(WHILE, "while");
    globalST->add(new STEntry(t, "while"));
}

// 2. MainClass -> class ID { public static void main(String[] ID){ Statement }}
void Parser::mainClass()
{
    match(CLASS);
    match(ID);
    match(LCHAVE);
    match(PUBLIC);
    match(STATIC);
    match(VOID);
    match(MAIN);
    match(LPAREN);
    match(STRING);
    match(LCOLCH);
    match(RCOLCH);
    match(ID);
    match(RPAREN);
    match(LCHAVE);
    statement();
    match(RCHAVE);
    match(RCHAVE);
}
// 3. ClassDeclaration → class ID (extends ID)? { (VarDeclaration)* (MethodDeclaration)*

void Parser::classDeclaration()
{
    match(CLASS);
    match(ID);
    if (lToken->name == EXTENDS)
    {
        advance();
        match(ID);
    }
    match(LCOLCH);
    while (lToken->name == BOOLEAN || lToken->name == INT || lToken->name == ID)
    {
        varDeclaration();
    }
    while (lToken->name == PUBLIC)
    {
        methodDeclaration();
    }

    match(RPAREN);
}
// 4. VarDeclaration -> Type ID ;
void Parser::varDeclaration()
{
    type();
    match(ID);
    match(PONTVIR);
}
// 5. MethodDeclaration -> public Type ID ( (Type ID) * ) { (VarDeclaration)* (Statement)* return Expression ; }
void Parser::methodDeclaration()
{
    match(PUBLIC);
    type();
    match(ID);
    match(LPAREN);
    if (lToken->name == BOOLEAN || lToken->name == INT || lToken->name == ID)
    {
        type();
        match(ID);
        while (lToken->name == VIRGULA)
        {
            match(VIRGULA);
            type();
            match(ID);
        }
    }
    match(RPAREN);
    match(LCHAVE);
    while (lToken->name == BOOLEAN || lToken->name == INT || lToken->name == ID)
    {
        varDeclaration();
    }
    while (lToken->name != RETURN)
    {
        statement();
    }
    match(RETURN);
    expression();
    match(PONTVIR);
    match(RCHAVE);
}
// 6. Type -> int [ ] | boolean | int | ID [ ]
void Parser::type()
{
    if (lToken->name == INT)
    {
        match(INT);
        if (lToken->name == LCOLCH)
        {
            match(LCOLCH);
            match(RCOLCH);
        }
    }
    else if (lToken->name == BOOLEAN)
    {
        match(BOOLEAN);
    }
    else if (lToken->name == ID)
    {
        match(ID);
        if (lToken->name == LCOLCH)
        {
            match(LCOLCH);
            match(RCOLCH);
        }
    }
    else
    {
        error("Tipo esperado");
    }
}
// 7. Statement -> { (Statement)* } | if ( Expression ) Statement (else Statement)?
// | while ( Expression ) Statement | System.out.println ( Expression ) ;
// | ID = Expression ; | ID [ Expression ] = Expression ;
void Parser::statement()
{
    switch (lToken->name)
    {
    case LCHAVE:
        match(LCHAVE);
        while (lToken->name != RCHAVE)
            statement();
        match(RCHAVE);
        break;
    case IF:
        match(IF);
        match(LPAREN);
        expression();
        match(RPAREN);
        statement();
        if (lToken->name == ELSE)
        {
            match(ELSE);
            statement();
        }
        break;
    case WHILE:
        match(WHILE);
        match(LPAREN);
        expression();
        match(RPAREN);
        statement();
        break;
    case SYSTEM:
        match(SYSTEM);
        match(PONTO);
        match(OUT);
        match(PONTO);
        match(PRINTLN);
        match(LPAREN);
        expression();
        match(RPAREN);
        match(PONTVIR);
        break;
    case ID:
        match(ID);
        if (lToken->name == EQUAL) // ID = Expression ;
        {
            match(EQUAL);
            expression();
            match(PONTVIR);
        }
        else if (lToken->name == LCOLCH) // ID [ Expression ] = Expression ;
        {
            match(LCOLCH);
            expression();
            match(RCOLCH);
            match(EQUAL);
            expression();
            match(PONTVIR);
        }
        else
        {
            error("Erro de sintaxe: statement inválido.");
        }
        break;
    default:
        error("Erro de sintaxe: statement inválido.");
        break;
    }
}

void Parser::expression()
{
    switch (lToken->name)
    {
    case INTEGER_LITERAL:
        match(INTEGER_LITERAL);
        break;
    case TRUE:
        match(TRUE);
        break;
    case FALSE:
        match(FALSE);
        break;
    case ID:
        match(ID);
        if (lToken->name == LCOLCH) // ID [ Expression ]
        {
            match(LCOLCH);
            expression();
            match(RCOLCH);
        }
        else if (lToken->name == PONTO) // ID . length | ID . ID ( ( Expression (, Expression)* )? )
        {
            match(PONTO);
            if (lToken->name == LENGTH)
            {
                match(LENGTH);
            }
            else if (lToken->name == ID)
            {
                match(ID);
                match(LPAREN);
                if (lToken->name != RPAREN)
                {
                    expression();
                    while (lToken->name == VIRGULA)
                    {
                        match(VIRGULA);
                        expression();
                    }
                }
                match(RPAREN);
            }
            else
            {
                error("Erro de sintaxe: ID inválido.");
            }
        }
        break;
    case THIS:
        match(THIS);
        break;
    case NEW:
        match(NEW);
        if (lToken->name == INT)
        {
            match(INT);
            match(LCOLCH);
            expression();
            match(RCOLCH);
        }
        else if (lToken->name == ID)
        {
            match(ID);
            match(LPAREN);
            match(RPAREN);
        }
        else
        {
            error("Erro de sintaxe: operação NEW inválida.");
        }
        break;
    case NOT:
        match(NOT);
        expression();
        break;
    case LPAREN:
        match(LPAREN);
        expression();
        match(RPAREN);
        break;
    }
}

void Parser::op()
{
    if (lToken->name == AND)
    {
        match(AND);
    }
    else if (lToken->name == LT)
    {
        match(LT);
    }
    else if (lToken->name == GT)
    {
        match(GT);
    }
    else if (lToken->name == EQUAL)
    {
        match(EQUAL);
    }
    else if (lToken->name == NOT_EQUAL)
    {
        match(NOT_EQUAL);
    }
    else if (lToken->name == ADD)
    {
        match(ADD);
    }
    else if (lToken->name == SUB)
    {
        match(SUB);
    }
    else if (lToken->name == MUL)
    {
        match(MUL);
    }
    else if (lToken->name == DIV)
    {
        match(DIV);
    }
    else
    {
        error("Operador esperado");
    }
}

void Parser::error(string str)
{
    cout << "Linha " << scanner->getLine() << ": " << str << endl;
    // Modo Pânico
    while (lToken->name != PONTVIR && lToken->name != RCHAVE && lToken->name != END_OF_FILE)
    {
        lToken = scanner->nextToken();
    }

    exit(EXIT_FAILURE);
}