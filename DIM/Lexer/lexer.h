#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

#include "tokens.h"

class Lexer {
public:
	explicit Lexer(std::string& original_text) : text_(original_text) { Advance(); } // Конструктор
	~Lexer() {} // Деструктор
	Token structure_token; // Структура токена
	std::map<std::string, std::string> CODE_VARIBLES; // Сигнатуры переменных в DIM коде
	std::map<std::string, std::string> CODE_STRING_LITERALS; // Сигнатуры строк в DIM коде
	std::map<std::string, std::string> CODE_DIGITS; // Сигнатуры цифр в DIM коде
	void Advance(int step = 1); // Следующий символ
	Token GetString(int first_quote_position, int second_quote_position); // Получить строку
	Token GetCommand(); // Получить команду
	Token GetDigit(); // Получить цыфру
	std::vector<Token> Lex(); // Разобрать текст на токены

private:
	// Зарегистрированные команды
	std::string REGISTRY_COMMANDS_[17] = { "out", "in", "len", "while", "for", "if", "else", "null", "Main", "len", "or", "and", "var"};
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
		{Logic_Operation_Tokens::EQUAL_TOKEN, Type::TYPE_EQUAL},				// =
		{Separator_Tokens::NEXT_LINE, Type::TYPE_NL}
	};
	std::map<std::string, std::string> WordsCode_ = {
		{"out", "W1"}, {"in", "W2"}, {"if", "W3"},
		{"else", "W4"}, {"while", "W5"}, {"for", "W6"},
		{"len", "W7"}, {"int", "W8"}, {"float", "W8"},
		{"bolean", "W8"}, {"var", "W8"}, {"null", "W9"},
		{"Main", "W10"}
	};
	std::map<char, std::string> SeparatorCode_ = {
		{'{', "S1"}, {'}', "S2"}, {'(', "S3"},
		{')', "S4"}, {';', "S5"}, {'\n', "S6"},
		{'\t', "S7"}, {'[', "S8"}, {']', "S9"}
	};
	std::map<char, std::string> MathAndUnaryLogicOperationCode_ = {
		{'+', "O1"}, {'-', "O2"}, {'/', "O3"},
		{'*', "O4"}, {'%', "O5"},
		{'>', "L1"}, {'<', "L2"}, {'=', "L3"}
	};
	std::map<std::string, std::string> BinaryLogicAndMathOperationCode_ = {
		{">=", "L4"}, {"<=", "L5"}, {"==", "L6"},
		{"!=", "L7"}, {"or", "L8"}, {"and", "L9"},
		{"++", "O6"}, {"--", "O7"}
	};
	int varible_count_ = 0; // счетчик переменных
	int string_literals_count_ = 0; // счетчик строковых литералов
	int digit_count_ = 0; // счетчик цифр
	std::string text_; // код 
	int position_ = -1; // Позиция элемента
	unsigned char current_char_ = '\0'; // Текущий символ
};
