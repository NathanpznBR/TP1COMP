#include "scanner.h"

int main(int argc, char* argv[]) 
{
    string input;
    
    getline(cin, input);

    Scanner* scanner = new Scanner(input);
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        cout << t->name << " ";
    }while (t->name != END_OF_FILE);

    delete scanner;

    return 0;
}