/************************************************
 *  Class : ExpressionEvaluator
 *  Author: github@Leopard-C
 *  Method: RPN(Reverse Polish Notation)
 *  Last Change: 2020-04-05
************************************************/
#ifndef __EXPRESSION_EVALUATOR_H__
#define __EXPRESSION_EVALUATOR_H__

#include <string>
#include <vector>

#define EXPEV_NO_ERROR 0

class ExpressionEvaluator {
public:

    double eval(const std::string& str);

    int getLastError() { return errorCode; }
    std::string getErrorDesc(int err_code = -1);

    const std::vector<std::string>& getRPN() { return rpn; };
    const std::string& getStdExp() { return stdExp; }

private:
    bool validate(std::string& str);
    bool parseToRPN(std::string& str, std::vector<std::string>& tokens);
    double evalRPN(std::vector<std::string>& tokens);

    bool isOperator(char c);
    bool isPartOfNumber(char c);    // [0-9.]
    bool isParenthesis(char c);

    // The priority of operator
    int priority(char op);

    bool toNumber(const std::string& str, double& val);

private:
    int errorCode = 0;
    std::string stdExp; // standardized expression;
    std::vector<std::string> rpn;
};

#endif //__EXPRESSION_EVALUATOR_H__

