#include <iostream>
#include "Postfix.h"

int main()
{
  std::string expression = "(2.3 + 1.7) * 3 + 28";
  double result;
  TArithmeticExpression expressionRes(expression);
  std::cout << expression << std::endl;
  std::cout << "Expression: " << expressionRes.getInfix() << std::endl;
  std::cout << "Postfix: " << expressionRes.getPostfix() << std::endl;
  result = expressionRes.calculate();
  std::cout << "ressult: " << result << std::endl;
  return 0;
}
