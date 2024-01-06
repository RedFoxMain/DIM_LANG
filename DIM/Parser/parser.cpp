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

bool Parser::InVector(std::vector<std::string> list, std::string& word) {
	bool in_vector = (std::find(begin(list), end(list), word) != end(list)) ? true : false;
	return in_vector;
}

void Parser::MakeFile(std::string& data) {
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
	for (size_t index = 0; index < hiddenData_.size(); ++index) {
		int nextIndex = index + 1;
		cpp_code += STRING_LITERALS_CODE_[hiddenData_[index].code];
		cpp_code += DIGITS_CODE_[hiddenData_[index].code];
		cpp_code += VARIBLES_CODE_[hiddenData_[index].code];
		cpp_code += OPN[hiddenData_[index].code];
		if (hiddenData_[index].type == Type::TYPE_RRB && !InVector({"{", "or", "and" }, hiddenData_[nextIndex].value)) { cpp_code += ";"; }
		if ((hiddenData_[index].type == Type::TYPE_INT || hiddenData_[index].type == Type::TYPE_FLOAT) && !InVector({")", "or", "and" }, hiddenData_[nextIndex].value)) { cpp_code += ";";}
		if (hiddenData_[index].type == Type::TYPE_INCREMENT || hiddenData_[index].type == Type::TYPE_DECREMENT) { cpp_code += ";"; }
		cpp_code += " ";
	}
	MakeFile(cpp_code);
	
}
