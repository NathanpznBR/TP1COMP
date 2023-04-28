#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input/*, SymbolTable* table*/)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    //st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

Token*
Scanner::nextToken()
{
    Token* tok;
    string lexeme;
    int state = 1;

    while (true)
    {
        while (isspace(input[pos]))
            pos++;
        switch (state)
        {
        case 1:
            //Op = ou ==
            if (input[pos] == '=')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, EQUAL);
                }
                else {
                    tok = new Token(OP, ASSIGN);
                }
            }
            // Op ! ou !=
            else if (input[pos] == '!')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, NOT_EQUAL);
                }
                else {
                    tok = new Token(OP, NOT);
                }
            }
            // Op >
            else if (input[pos] == '>')
            {
                pos++;
                tok = new Token(OP, GT);
            }
            //Op <
            else if (input[pos] == '<')
            {
                pos++;
                tok = new Token(OP, LT);
            }
            //Op +
            else if (input[pos] == '+')
            {
                pos++;
                tok = new Token(OP, ADD);
            }
            //Op -
            else if (input[pos] == '-')
            {
                pos++;
                tok = new Token(OP, SUB);
            }
            //Op *
            else if (input[pos] == '*')
            {
                pos++;
                tok = new Token(OP, MUL);
            }
            //Op / ou comentário
            else if (input[pos] == '/')
            {
                pos++;
                // comentário de linha
                if (input[pos] == '/') {
                    while (input[pos] != '\n')
                        pos++;
                    state = 1;
                    //ignora o comentário
                    //procura o próximo token
                }
                // comentário de bloco
                else if (input[pos] == '*') {
                    state = 2;
                }
                // Op /
                else {
                    tok = new Token(OP, DIV);
                }
            }
            // Sep ;
            else if (input[pos] == ';') {
                pos++;
                tok = new Token(SEP, PONTVIR);
            }
            // Sep (
            else if (input[pos] == '(') {
                pos++;
                tok = new Token(SEP, LPAREN);
            }
            // Sep )
            else if (input[pos] == ')') {
                pos++;
                tok = new Token(SEP, RPAREN);
            }
            // Sep {
            else if (input[pos] == '{') {
                pos++;
                tok = new Token(SEP, LCHAVE);
            }
            // Sep }
            else if (input[pos] == '}') {
                pos++;
                tok = new Token(SEP, RCHAVE);
            }
            // Sep ]
            else if (input[pos] == ']') {
                pos++;
                tok = new Token(SEP, LCOLCH);
            }
            // Sep [
            else if (input[pos] == '[') {
                pos++;
                tok = new Token(SEP, RCOLCH);
            }
            // Sep ,
            else if (input[pos] == ',') {
                pos++;
                tok = new Token(SEP, VIRGULA);
            }
            // Sep .
            else if (input[pos] == '.') {
                pos++;
                tok = new Token(SEP, PONTO);
            }
            // Número inteiro
            else if (isdigit(input[pos])) {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
                tok = new Token(INTEGER_LITERAL);
            }
            // ID ou palavra reservada
            /*else if (isalpha(input[pos]) || input[pos] == '_') {
                pos++;
                while (isalpha(input[pos]) || isdigit(input[pos]) || input[pos] == '_')
                    pos++;
                //Pesquisar na tabela de palavras reservadas
                //Caso não encontre, o Token é ID
                //Se não, retorne o Token adequado
                STEntry* obj = st->get(lexeme);
                if (!obj) {
                    tok = new Token(ID);
                    STEntry* IDreserved;
                    IDreserved = new STEntry(tok, lexeme, true);
                    add(IDreserved);
                }
                else
                    tok = new Token(obj->token->name);
            }
            //String
            else if (input[pos] == '"') {
                pos++;
                while(input[pos++] != '"')
                    pos++;
                tok = new Token(STRING_LITERAL);
            }*/
            //final de arquivo
            else if (input[pos] == '\0')
                tok = new Token(END_OF_FILE);
            return tok;
        case 2:
            // Comentário /* qualquer coisa até encontrar *
            while (input[pos] != '*')
                pos++;
            //ao encontrar * vai para o estado 3
            state = 3;
        case 3:
            //se encontrar / encerra o comentário
            if (input[pos] == '/') {
                pos++;
                // vai para o estado um para encontrar o token
                state = 1;
            }
            else //se não encontrar / volta a procurar *
                state = 2;
        }
    }
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
