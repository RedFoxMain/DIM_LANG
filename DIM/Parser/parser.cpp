#include <iostream>
#include "parser.h"

void Parser::GetStrings(std::map<std::string, std::string> &strings) {
	for (const auto& it : strings) {
		STRING_LITERALS_CODE_[it.second] = it.first;
	}
}

void Parser::GetDigits(std::map<std::string, std::string>& digits) {
	for (const auto& it : digits) {
		DIGITS_CODE_[it.second] = it.first;
	}
}

void Parser::GetVaribles(std::map<std::string, std::string>& varibles) {
	for (const auto& it : varibles) {
		VARIBLES_CODE_[it.second] = it.first;
	}
}

void Parser::MakeFile(std::string data) {
	std::ofstream out;
	out.open("release.cpp");
	if (out.is_open())
	{
		out << data;
	}
	out.close();
}

void Parser::TarnslateToCpp() {
	std::string cpp_code = "#include <iostream>\n";
	for (const auto& el: hiddenData_) {
		cpp_code += STRING_LITERALS_CODE_[el.code];
		cpp_code += DIGITS_CODE_[el.code];
		cpp_code += VARIBLES_CODE_[el.code];
		cpp_code += OPN[el.code];
		if (el.type == Type::TYPE_EOL || el.type == Type::TYPE_RFB || el.type == Type::TYPE_LFB) { cpp_code += "\n"; }
		cpp_code += " ";
	}
	MakeFile(cpp_code);
}
