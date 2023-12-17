#include <string>
#include <vector>
#include <utility>
#include <map>
#include "TStack.h"

class TArithmeticExpression {
private:
    std::string infix;
    std::string postfix;

    std::vector<std::string> simpleLook;
    std::map<std::string, int> priority;
    std::map<std::string, double> operands;

    void toSimpleLook();
    void toPostfix();

public:
    TArithmeticExpression(std::string expression = "");

    std::string getInfix() const { return infix; }
    std::string getPostfix() const { return postfix; }

    std::vector<std::string> getOperands() const;
    double calculate();
};