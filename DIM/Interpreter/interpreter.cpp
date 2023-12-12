#include <iostream>

#define DEBUG true

#include "lexer.h"


void PrintLexerResult(std::vector<Token> tokens) {
	for (size_t i = 0; i < tokens.size(); ++i) {
		std::cout << tokens[i].code << " ";
		//std::cout << tokens[i].code << " ";
		if (tokens[i].type == Type::TYPE_EOL) {
			std::cout << '\n';
		}
	}
}


int main() {
	std::setlocale(LC_ALL, "Ru");
	std::string text = "int a = 5;\nif((a >= 5 || a < 10) && a != 9){\nout \"Yes\";}\n";

	Lexer lexer(text);

	std::vector<Token>tokens = lexer.Lex();
	
	if (DEBUG) { PrintLexerResult(tokens); }

	return 0;
}
