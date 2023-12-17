#include "Postfix.h"

void TArithmeticExpression::toSimpleLook() {
	std::string currentSimpleLook = "";
	for (char symbol : infix) {
		switch (symbol) {
		case '+': case '-': case '*': case '/': case '(': case ')':
			if (currentSimpleLook != "") {
				simpleLook.push_back(currentSimpleLook);
				currentSimpleLook = "";
			}

			currentSimpleLook += symbol;
			simpleLook.push_back(currentSimpleLook);
			currentSimpleLook = "";
			break;
		default:
			if ((symbol >= '0' && symbol <= '9') || symbol == '.' || symbol == ',') {
				currentSimpleLook += symbol;
			}
			break;
		}
	}
	if (currentSimpleLook != "") simpleLook.push_back(currentSimpleLook);
}

void TArithmeticExpression::toPostfix() {
	toSimpleLook();
	TStack<std::string> stack;
	std::string stackItem;

	for (std::string item : simpleLook) {
		switch (item[0]) {
		case '(':
			stack.Push(item);
			break;
		case ')':
			stackItem = stack.Top();
			stack.Pop();
			while (stackItem[0] != '(') {
				postfix += stackItem;
				postfix += " ";
				stackItem = stack.Top();
				stack.Pop();
			}
			break;
		case '+': case '-': case '*': case '/':
			while (!stack.IsEmpty()) {
				stackItem = stack.Top();
				stack.Pop();
				if (priority[item] <= priority[stackItem]) {
					postfix += stackItem;
					postfix += " ";
				}
				else {
					stack.Push(stackItem);
					break;
				}
			}
			stack.Push(item);
			break;
		default:
			operands.insert({item, 0.0});
			postfix += item;
			postfix += " ";
			break;
		}
	}
	while (!stack.IsEmpty()) {
		stackItem = stack.Top();
		stack.Pop();
		postfix += stackItem;
		postfix += " ";
	}

}

TArithmeticExpression::TArithmeticExpression(std::string expression) : infix(expression) {
	priority = { { "+", 1}, { "-", 1}, { "*", 2}, { "/", 2}, { "(", 0 } };
	toPostfix();
}

std::vector<std::string> TArithmeticExpression::getOperands() const {
	std::vector<std::string> res;
	for (const auto& item : operands) {
		res.push_back(item.first);
	}
	return res;
}

double TArithmeticExpression::calculate() {
	TStack<double> stack;
	double leftOperand, rightOperand;
	std::string currentLexeme = "";

	for (char symbol : postfix) {
		switch (symbol) {
		case '+': 
			rightOperand = stack.Top();
			stack.Pop();
			leftOperand = stack.Top();
			stack.Pop();
			stack.Push(leftOperand + rightOperand);
			break;
		case '-':
			rightOperand = stack.Top();
			stack.Pop();
			leftOperand = stack.Top();
			stack.Pop();
			stack.Push(leftOperand - rightOperand);
			break;
		case '*':
			rightOperand = stack.Top();
			stack.Pop();
			leftOperand = stack.Top();
			stack.Pop();
			stack.Push(leftOperand * rightOperand);
			break;
		case '/':
			rightOperand = stack.Top();
			stack.Pop();
			leftOperand = stack.Top();
			stack.Pop();
			stack.Push(leftOperand / rightOperand);
			break;
		default:
			if ((symbol >= '0' && symbol <= '9') || symbol == '.' || symbol == ',') {
				currentLexeme += symbol;
			}
			else {
				if (currentLexeme != "") {
					stack.Push(std::stod(currentLexeme));
					currentLexeme = "";
				}
			}
			break;
		}
	}

	return stack.Top();
}