#include <vector>

#include "tokens.h"
#include "opn.h"


class Parser {
public:
	explicit Parser(std::vector<Token> data): hiddenData_(data) {} // Конструктор
	~Parser(){} // Деструктор

private:
	std::vector<Token> hiddenData_; // Вектор закодированных ключевых слов DIM
};
