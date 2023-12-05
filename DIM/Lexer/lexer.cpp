#include <iostream>

#include "lexer.h"

// Имплементация Advance
void Lexer::Advance() {
	++position_;
	current_char_ = (position_ < text_.length()) ? text_[position_] : '\0';
}

// Имплементация GetString
Token Lexer::GetString(int first_quote_position, int second_quote_position) {
	std::string temp_string = "";
	for (; first_quote_position <= second_quote_position; ++first_quote_position) {
		temp_string += text_[first_quote_position];
		Advance();
	}
	
	structure_token.type = Type::TYPE_STRING;
	structure_token.value = temp_string;
	structure_token.token_position = position_ - text_.length();
	return structure_token;
}

// Имплементация GetCommand
Token Lexer::GetCommand() {
	std::string temp_string = "";
	
	while (std::isalpha(current_char_)) {
		temp_string += current_char_;
		Advance();
	}
	
	// Проверяем, является ли temp_string командой
	bool is_registry_command = (std::find(begin(REGISTRY_COMMANDS_), end(REGISTRY_COMMANDS_), temp_string) != end(REGISTRY_COMMANDS_)) ? true : false;
	
	if (is_registry_command){
		structure_token.type = Type::TYPE_COMMAND;
		structure_token.value = temp_string;
		structure_token.token_position = position_ - temp_string.length();
		return structure_token;
	}else {
		// Если temp_string нет в REGISTRY_COMMANDS_ вероятно это переменная
		structure_token.type = Type::TYPE_VARIBLE;
		structure_token.value = temp_string;
		structure_token.token_position = position_ - temp_string.length();
		return structure_token;
		
	}
} 

// Имплементация GetDigit
Token Lexer::GetDigit() {
	std::string temp_digit = "";
	while (std::isdigit(current_char_) || current_char_ == Separator_Tokens::DOT_TOKEN) {
		temp_digit += current_char_;
		Advance();
	}
	// Проверяем, является ли temp_digit числом с плавающей точкой
	bool is_float = (temp_digit.find(Separator_Tokens::DOT_TOKEN) != std::string::npos);

	structure_token.type = is_float ? Type::TYPE_FLOAT : Type::TYPE_INT;
	structure_token.value = temp_digit;
	structure_token.token_position = position_ - temp_digit.length();
	return structure_token;
}

// Главный метод для анализа токенов
std::vector<Token> Lexer::Lex() {
	std::vector<Token> tokens;
	int first_quote_position = -1, second_quote_position;
	while (position_ < text_.length()) {
		
		// Пропустить пробелы
		if (std::isspace(current_char_)) {
			Advance();
			continue;
		}

		if (current_char_ == Separator_Tokens::QUOTE_TOKEN) { first_quote_position = position_; } // найти позицию "

		// Получить >=
		if (current_char_ == Logic_Operation_Tokens::GREATER_TOKEN && text_[position_+1] == Logic_Operation_Tokens::EQUAL_TOKEN) {
			structure_token.type = Type::TYPE_GREATER_EQUAL;
			structure_token.value = ">=";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}

		// Получить <=
		if (current_char_ == Logic_Operation_Tokens::LESS_TOKEN && text_[position_ + 1] == Logic_Operation_Tokens::EQUAL_TOKEN) {
			structure_token.type = Type::TYPE_LESS_EQUAL;
			structure_token.value = "<=";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}
		
		// Получить ==
		if (current_char_ == Logic_Operation_Tokens::EQUAL_TOKEN && text_[position_ + 1] == Logic_Operation_Tokens::EQUAL_TOKEN) {
			structure_token.type = Type::TYPE_EQUAL_EQUAL;
			structure_token.value = "==";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}

		// Получить !=
		if (current_char_ == Logic_Operation_Tokens::FACTORIAL_TOKEN && text_[position_ + 1] == Logic_Operation_Tokens::EQUAL_TOKEN) {
			structure_token.type = Type::TYPE_NOT_EQUAL;
			structure_token.value = "!=";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}

		// Получить ++
		if (current_char_ == Math_Operation_Tokens::ADD_TOKEN && text_[position_ + 1] == Math_Operation_Tokens::ADD_TOKEN) {
			structure_token.type = Type::TYPE_INCREMENT;
			structure_token.value = "++";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}

		// Получить --
		if (current_char_ == Math_Operation_Tokens::SUBDIVIDE_TOKEN && text_[position_ + 1] == Math_Operation_Tokens::SUBDIVIDE_TOKEN) {
			structure_token.type = Type::TYPE_DECREMENT;
			structure_token.value = "--";
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
			Advance();
			continue;
		}

		// Собрать цифры
		if (std::isdigit(current_char_) || current_char_ == Separator_Tokens::DOT_TOKEN) {
			tokens.push_back(GetDigit());
			continue;
		}

		// Собрать строку
		if (first_quote_position > 0) {
			second_quote_position = text_.find(QUOTE_TOKEN, first_quote_position + 1);
			tokens.push_back(GetString(first_quote_position, second_quote_position));
			first_quote_position = -1;
			continue;
		}

		// Собрать команду
		if (std::isalpha(current_char_)) {
			tokens.push_back(GetCommand());

			continue;
		}

		// Присвоить тип, значение, позицию оставшимся элементам
		if (TOKEN_TABLE_.count(current_char_) > 0) {
			structure_token.type = TOKEN_TABLE_[current_char_];
			structure_token.value = current_char_;
			structure_token.token_position = position_;
			tokens.push_back(structure_token);
		}else {
			// бросить ошибку о неизвестном токене
			std::cout << "Неизвестный токен: " << position_ << '\n';
			exit(1);
		}
		Advance(); // Следующий символ
	}
	return tokens;
}
