#pragma once
#include <map>
#include <string>

// (ОПН) Обратная Польская Нотация
std::map<std::string, std::string> OPN = {
	{"W1", "std::cout"}, {"W2", "getline"}, {"W3", "if"},
	{"W4", "else"},   {"W5", "while"},   {"W6", "for"},
	{"W7", "size()"}, {"W8", "printf"},  {"W9", "printf"},
	{"W8", "auto"}, {"W9", "null", }, {"W10", "Main"},
	{"S1", "{"}, {"S2", "}"}, {"S3", "("}, {"S4", ")"},
	{"S5", ";"}, {"S6", "\n"}, {"S7", "\t"}, {"S8", "["}, 
	{"S9", "]"}, {"S10", "//"}, {"O1", "+"}, {"O2", "-"}, 
	{"O3", "/"}, {"O4", "*"}, {"O5", "%"}, {"L1", ">"}, 
	{"L2", "<"}, {"L3", "="}, {"L4", ">="}, {"L5", "<="},
	{"L6", "=="}, {"L7", "!="}, {"L8", "||"}, {"L9", "&&"}, 
	{"O6", "++"}, {"O7", "--"}
};

std::map<std::string, std::string> VARIBLES_CODE; // получить переменную по коду
std::map<std::string, std::string> STRING_LITERALS_CODE; // получить строку по коду
std::map<std::string, std::string> DIGITS_CODE; // получить цифру по коду
