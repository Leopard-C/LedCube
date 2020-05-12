#include "ExpressionEvaluator.h"

#include <cmath>
#include <sstream>
#include <stack>
#include <algorithm>


double ExpressionEvaluator::eval(const std::string& strIn) {
    std::string str = strIn;

    // reset errorCode to 0: no error
    // clear rpn
    errorCode = 0;
    std::vector<std::string>().swap(rpn);

    // Empty expression
    if (str.empty()) {
        errorCode = 0x06;
        return 0;
    }

    // check validation
    if (!validate(str)) {
        return 0;
    }

    // parse and convert to RPN (Reverse Polish Notation)
    parseToRPN(str, rpn);

    // evaluate
    return evalRPN(rpn);
}


// Check validation and standardize the input expression
bool ExpressionEvaluator::validate(std::string& str) {
    size_t len = str.length();
    std::vector<bool> eraseFlag(len, false);
    char prevChar = 0;
    bool prevCharIsNumber = false;
    bool prevCharIsOperator = false;
    bool isSeparated = false;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ' ') {
            eraseFlag[i] = true;
            isSeparated = true;
        }
        else if (isPartOfNumber(str[i])) {
            if (prevCharIsNumber && isSeparated) {
                errorCode = 0x01;
                return false;   // ERROR: the number is separated
            }
            prevChar = str[i];
            prevCharIsNumber = true;
            prevCharIsOperator = false;
            isSeparated = false;
        }
        else if (isOperator(str[i])) {
            prevChar = str[i];
            if (prevCharIsOperator) {
                if (str[i] == '-') {
                    prevCharIsNumber = true;    // the negative sign (a part of number)
                    prevCharIsOperator = false;
                    isSeparated = false;
                }
                else {
                    errorCode = 0x02;
                    return false;   // ERROR: two continuous operators
                }
            }
            else {
                prevCharIsOperator = true;
                prevCharIsNumber = false;
                isSeparated = false;
            }
        }
        else if (isParenthesis(str[i])) {
            prevCharIsOperator = false;
            prevCharIsNumber = false;
            isSeparated = false;
        }
        else {
            errorCode = 0x03;
            return false;
        }
    }

    std::string oldStr;
    oldStr.swap(str);

    for (size_t i = 0; i < len; ++i) {
        if (!eraseFlag[i]) {
            str.push_back(oldStr[i]);
        }
    }

    // Empty expression
    if (str.empty()) {
        errorCode = 0x06;
        return false;
    }

    // Start with an operator
    if (isOperator(str[0])) {
        if (str[0] == '-') {
            if (str.size() > 1 && str[1] == '-') {
                errorCode = 0x04;
                return false;
            }
        }
        else {
            errorCode = 0x04;
            return false;
        }
    }

    // End with an operator
    if (isOperator(str.back())) {
        errorCode = 0x05;
        return false;
    }

    // Parenthesis doesn't match
    size_t numLeftPar = std::count(str.begin(), str.end(), '(');
    size_t numRightPar = std::count(str.begin(), str.end(), ')');
    if (numLeftPar != numRightPar) {
        errorCode = 0x07;
        return false;
    }

    stdExp = str;

    // Start width '-'
    // Push front a '0'
    if (str[0] == '-') {
        str.insert(0, "0");
    }

    return true;
}


// Parse and convert to RPN
// The input str must be standardized
bool ExpressionEvaluator::parseToRPN(std::string& str, std::vector<std::string>& tokens) {
    std::stack<char> sOperator;

    size_t len = str.length();
    int idx = 0;
    bool prevIsOperator = true;
    while (idx < len) {
        // number
        if (isPartOfNumber(str[idx]) || (str[idx] == '-' && prevIsOperator)) {
            int start = idx;
            idx++;
            while (idx < len && isPartOfNumber(str[idx])) {
                idx++;
            }
            tokens.push_back(str.substr(start, idx - start));
            prevIsOperator = false;
        }
        // '('
        else if (str[idx] == '(') {
            prevIsOperator = true;
            sOperator.push('(');
            idx++;
        }
        // operator
        else if (isOperator(str[idx])) {
            char op = str[idx];
            while (1) {
                if (sOperator.empty() || sOperator.top() == '(') {
                    sOperator.push(op);
                    break;
                }
                if (priority(op) < priority(sOperator.top())) {
                    sOperator.push(op);
                    break;
                }
                else {
                    std::string opStr;
                    opStr.push_back(sOperator.top());
                    tokens.push_back(opStr);
                    sOperator.pop();
                    continue;
                }
            }
            prevIsOperator = true;
            idx++;
        }
        // ')'
        else if (str[idx] == ')') {
            while (!sOperator.empty() && sOperator.top() != '(') {
                std::string opStr;
                opStr.push_back(sOperator.top());
                tokens.push_back(opStr);
                sOperator.pop();
            }
            sOperator.pop();
            prevIsOperator = true;
            idx++;
        }
        else {
            // You won't actually get here
        }
    }

    while (!sOperator.empty()) {
        std::string opStr;
        opStr.push_back(sOperator.top());
        tokens.push_back(opStr);
        sOperator.pop();
    }

    return true;
}

// evaluate the RPN
double ExpressionEvaluator::evalRPN(std::vector<std::string>& tokens) {
    std::stack<double> nums;
    for (auto token : tokens) {
        double num;
        if (toNumber(token, num)) {
            nums.push(num);
        }
        else {
            double rightOperand = nums.top();
            nums.pop();
            double leftOperand = nums.top();
            nums.pop();
            char op = token[0];
            double result = 0;
            switch (op) {
            case '+':
                result = leftOperand + rightOperand;
                break;
            case '-':
                result = leftOperand - rightOperand;
                break;
            case '*':
                result = leftOperand * rightOperand;
                break;
            case '/':
                result = leftOperand / rightOperand;
                break;
            case '%':
                result = int(leftOperand) % int(rightOperand);
                break;
            case '^':
                result = pow(leftOperand, rightOperand);
                break;
            default:
                // Won't come done here
                break;
            }
            nums.push(result);
        }
    }

    if (nums.empty())
        return 0;
    else
        return nums.top();
}

bool ExpressionEvaluator::isPartOfNumber(char c) {
    return  (c >= '0' && c <= '9') || c == '.';
}

bool ExpressionEvaluator::isParenthesis(char c) {
    return c == '(' || c == ')';
}

bool ExpressionEvaluator::isOperator(char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
        return true;
    default:
        return false;
    }
}

bool ExpressionEvaluator::toNumber(const std::string& str, double& val) {
    std::stringstream ssIn(str);
    double d;
    char c;
    if (!(ssIn >> d))
        return false;
    if (ssIn >> c)
        return false;
    val = d;
    return true;
}

int ExpressionEvaluator::priority(char op) {
    switch (op) {
    case '^':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 3;
    default:
        return -1;  // won't happen
    }
}


std::string ExpressionEvaluator::getErrorDesc(int err_code) {
    if (err_code == -1)
        err_code = this->errorCode;

    switch(err_code) {
    case 0x00:
        return "No Error";
    case 0x01:
        return "ERROR: The number is separated";
    case 0x02:
        return "ERROR: Two continuous operators";
    case 0x03:
        return "ERROR: Unknown character";
    case 0x04:
        return "ERROR: Start with an operator";
    case 0x05:
        return "ERROR: End with an operator";
    case 0x06:
        return "ERROR: Empty expression";
    case 0x07:
        return "ERROR: Unmatched parentheses";
    default:
        return "Unknown error";
    }
}

