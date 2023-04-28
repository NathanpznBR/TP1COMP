#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	

	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}
// .1 Program -> MainClass (ClassDeclaration) * EOF
void
Parser::program()
{
	//TODO
    mainClass();

	while(lToken->name == CLASS) {
		classDeclaration();
	}

	match(EOF);
}

//Continuar....

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

// 2. MainClass -> class ID { public static void main(String[] ID){ Statement }}
void
Parser::mainClass()
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
}
void Parser::classDeclaration()
{
	match(CLASS);
	match(ID);
	if(lToken->name == EXTENDS) {
		match(EXTENDS);
		match(ID);
	}
	match(LBRACE);
	while(lToken->name == BOOLEAN || lToken->name == INT || lToken->name == ID) {
		varDeclaration();
	}
	while(lToken->name == PUBLIC) {
		methodDeclaration();
	}
	
	match(RBRACE);

}
// 4. VarDeclaration -> Type ID ;
void
Parser::varDeclaration()
{
	type();
	match(ID);
	match(PONTVIR);
}

void
Parser::methodDeclaration()
{
	match(PUBLIC);
	type();
	match(ID);
	match(LPAREN);
	if (lToken->name == BOOLEAN || lToken->name == INT
		|| lToken->name == ID) {
		type();
		match(ID);
		while (lToken->name == VIRGULA) {
			match(VIRGULA);
			type();
			match(ID);
		}
	}
	match(RPAREN);
	match(LCHAVE);
	while (lToken->name == BOOLEAN || lToken->name == INT
		   || lToken->name == ID) {
		varDeclaration();
	}
	while (lToken->name != RETURN) {
		statement();
	}
	match(RETURN);
	expression();
	match(PONTVIR);
	match(RCHAVE);
}

void
Parser::type()
{
	if (lToken->name == INT) {
		match(INT);
		if (lToken->name == LBRACKET) {
			match(LBRACKET);
			match(RBRACKET);
		}
	} else if (lToken->name == BOOLEAN) {
		match(BOOLEAN);
	} else if (lToken->name == ID) {
		match(ID);
		if (lToken->name == LBRACKET) {
			match(LBRACKET);
			match(RBRACKET);
		}
	} else {
		error("Tipo esperado");
	}
}

void Parser::statement()
{
    switch(lToken->name)
    {
        case '{':
            match('{');
            while(lToken->name != '}')
                statement();
            match('}');
            break;
        case IF:
            match(IF);
            match('(');
            expression();
            match(')');
            statement();
            if(lToken->name == ELSE)
            {
                match(ELSE);
                statement();
            }
            break;
        case WHILE:
            match(WHILE);
            match('(');
            expression();
            match(')');
            statement();
            break;
        case SYSTEM:
            match(SYSTEM);
            match('.');
            match(OUT);
            match('.');
            match(PRINTLN);
            match('(');
            expression();
            match(')');
            match(';');
            break;
        case ID:
            match(ID);
            if(lToken->name == '=') // ID = Expression ;
            {
                match('=');
                expression();
                match(';');
            }
            else if(lToken->name == '[') // ID [ Expression ] = Expression ;
            {
                match('[');
                expression();
                match(']');
                match('=');
                expression();
                match(';');
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
    switch(lToken->name)
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
            if(lToken->name == '[') // ID [ Expression ]
            {
                match('[');
                expression();
                match(']');
            }
            else if(lToken->name == '.') // ID . length | ID . ID ( ( Expression (, Expression)* )? )
            {
                match('.');
                if(lToken->name == LENGTH)
                {
                    match(LENGTH);
                }
                else if(lToken->name == ID)
                {
                    match(ID);
                    match('(');
                    if(lToken->name != ')')
                    {
                        expression();
                        while(lToken->name == ',')
                        {
                            match(',');
                            expression();
                        }
                    }
                    match(')');
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
            if(lToken->name == INT)
            {
                match(INT);
                match('[');
                expression();
                match(']');
            }
            else if(lToken->name == ID)
            {
                match(ID);
                match('(');
                match(')');
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
        case '(':
            match(LPAREN);
			expression();
			match(RPAREN);
			break;

void Parser::op()
{
    if (lToken->name == AND) {
        match(AND);
    } else if (lToken->name == LT) {
        match(LT);
    } else if (lToken->name == GT) {
        match(GT);
    } else if (lToken->name == EQUAL) {
        match(EQUAL);
    } else if (lToken->name == NOT_EQUAL) {
        match(NOT_EQUAL);
    } else if (lToken->name == ADD) {
        match(ADD);
    } else if (lToken->name == SUB) {
        match(SUB);
    } else if (lToken->name == MUL) {
        match(MUL);
    } else if (lToken->name == DIV) {
        match(DIV);
    } else {
        error("Operador esperado");
    }
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
