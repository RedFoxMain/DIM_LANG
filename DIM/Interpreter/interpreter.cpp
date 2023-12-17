#include <iostream>
#include <fstream> 
#include <chrono>

#define DEBUG true

#include "lexer.h"

void PrintLexerResult(std::vector<Token> tokens) {
	for (size_t i = 0; i < tokens.size(); ++i) {
		std::cout << tokens[i].code << " ";
		if (tokens[i].type == Type::TYPE_EOL) {
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}

int main() {
	std::setlocale(LC_ALL, "Ru");
	std::string text;
	std::string line;
	std::ifstream file("dim_code.dim");
	if (file.is_open()) {
		while (file >> line) {
			text += line + ' ';
		}
	}else{ file.close(); }
	
	auto start_time = std::chrono::system_clock::now();
	Lexer lexer(text);
	auto end_time = std::chrono::system_clock::now();

	if (DEBUG) { PrintLexerResult(lexer.Lex()); }

	std::chrono::duration<double> duration = end_time - start_time;

	std::cout << "Выполнено без ошибок за: " << duration.count() << " секунд" << '\n'; // Лучшее время 0,00023
	return 0;
}
