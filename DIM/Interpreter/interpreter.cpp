#include <iostream>
#include <fstream> 
#include <chrono>

#include "lexer.h"
#include "parser.h"

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

	Parser parser(lexer.Lex());
	parser.TarnslateToCpp();

	std::chrono::duration<double> duration = end_time - start_time;

	std::cout << "Выполнено без ошибок за: " << duration.count() << " секунд" << '\n'; // Лучшее время 0,00022  
	return 0;
}
