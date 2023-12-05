#include <iostream>

#define DEBUG true

#include "lexer.h"
#include "parser.h"

void PrintLexerResult(std::vector<Token> tokens) {
	for (size_t i = 0; i < tokens.size(); ++i) {
		std::cout << tokens[i].value << "-Type:" << tokens[i].type << " ";
		if (tokens[i].type == Type::TYPE_EOL) {
			std::cout << '\n';
		}
	}
}

int main() {
	std::setlocale(LC_ALL, "Ru");
	std::string text = "out 6.0 != 7;\nout 5.0 >= 7;\nout 1.0 <= 7;\nout 7.0 == 7;\nout 5 + 6 - 5;\n~out \"Hello, World! 123\";\n~out \"Привет, Мир!\";\nvar a = 5;\nout a--;\nout a++;";

	Lexer lexer(text);
	std::vector<Token> tokens = lexer.Lex();
	
	if (DEBUG) { PrintLexerResult(tokens); }

	Parser parser(tokens);
	
	std::cout << parser.Parse();
	
	
	return 0;
}

