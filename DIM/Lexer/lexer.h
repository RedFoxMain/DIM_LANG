#pragma once
#include <vector>
#include <string>
#include <map>
#include <cctype>

#include "tokens.h"


class Lexer {
public:
	Token structure_token;
	
	explicit Lexer(std::string& original_text) : text_(original_text) { Advance(); } // Конструктор
	void Advance(); // Следующий символ
	Token GetString(int first_quote_position, int second_quote_position); // Получить строку
	Token GetCommand(); // Получить команду
	Token GetDigit(); // Получить цыфру
	std::vector<Token> Lex(); // Разобрать текст на токены
	
private:
	// Зарегистрированные команды
	std::string REGISTRY_COMMANDS_[8] = { "out", "in", "len", "while", "for", "if", "else", "var"};
	// Таблица токенов
	std::map<char, Type> TOKEN_TABLE_ = {
		{Math_Operation_Tokens::ADD_TOKEN, Type::TYPE_ADD},						// +
		{Math_Operation_Tokens::SUBDIVIDE_TOKEN, Type::TYPE_SUBDIVIDE},			// -
		{Math_Operation_Tokens::MULTIPLY_TOKEN, Type::TYPE_MULTIPLY},			// *
		{Math_Operation_Tokens::DIVIDE_TOKEN, Type::TYPE_DIVIDE},				// /
		{Logic_Operation_Tokens::GREATER_TOKEN, Type::TYPE_GREATER},		    // >
		{Logic_Operation_Tokens::LESS_TOKEN, Type::TYPE_LESS},					// <
		{Barackets_Tokens::LSB_TOKEN, Type::TYPE_LSB},							// [
		{Barackets_Tokens::RSB_TOKEN, Type::TYPE_RSB},							// ]
		{Barackets_Tokens::LRB_TOKEN, Type::TYPE_LRB},							// (
		{Barackets_Tokens::RRB_TOKEN, Type::TYPE_RRB},							// )
		{Barackets_Tokens::LFB_TOKEN, Type::TYPE_LFB},							// {
		{Barackets_Tokens::RFB_TOKEN, Type::TYPE_RFB},							// }
		{Separator_Tokens::EOL_TOKEN, Type::TYPE_EOL},							// ;
		{Separator_Tokens::COMMENT_TOKEN, Type::TYPE_COMMENT},					// ~
		{Logic_Operation_Tokens::EQUAL_TOKEN, Type::TYPE_EQUAL}					// =
	};
	std::string text_; // код 
	int position_ = -1; // Позиция элемента
	unsigned char current_char_ = '\0'; // Текущий символ
};
