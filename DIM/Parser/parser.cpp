#include <iostream>
#include "parser.h"

bool Parser::StartsWith(const std::string& text, std::string start) {
	if (text.rfind(start)) { return true; }
	return false;
}

void Parser::TarnslateToCpp() {
	
	
	std::string cpp_code = "";
	for (const auto& el: hiddenData_) {
		if (StartsWith(el.code, "I")) { cpp_code += VARIBLES_CODE[el.code]; }
		if (StartsWith(el.code, "C")) { cpp_code += STRING_LITERALS_CODE[el.code];}
		if (StartsWith(el.code, "N")) { cpp_code += DIGITS_CODE[el.code];}
		cpp_code += OPN[el.code];
		if (el.type == Type::TYPE_EOL || el.type == Type::TYPE_RFB || el.type == Type::TYPE_LFB) { cpp_code += "\n"; }
		cpp_code += " ";
	}
	std::cout << cpp_code << std::endl;
}
