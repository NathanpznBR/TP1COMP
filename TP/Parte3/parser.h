#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable* globalST;
    	SymbolTable* currentST;

		void advance();
		void match(int);
		
	public:
		Parser(string);
		void run();
        void program();
		void classList();
		void initSimbolTable();
        void mainClass();
		void classDeclaration();
		void varDeclaration();
		void methodDeclaration();
		void type();
		void statement();
		void expression();
		void op();
        void error(string);
};