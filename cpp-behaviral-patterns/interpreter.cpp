#include <iostream>

class Expression {
public:
    virtual int evaluate() = 0;
};

class OperationExpression : public Expression {
    std::string operatorSymbol;
    Expression *lhs;
    Expression *rhs;
public:
    OperationExpression(const std::string &operatorSymbol,
                        Expression *lhs, Expression *rhs) : operatorSymbol(operatorSymbol),
                                                            lhs(lhs), rhs(rhs) {}
    int evaluate() override {
        if (operatorSymbol == "plus") {
            return lhs->evaluate() + rhs->evaluate();
        } else if (operatorSymbol == "minus") {
            return lhs->evaluate() - rhs->evaluate();
        } else {
            std::cout << "Unrecognized operator: " << operatorSymbol;
            return 0;
        }
        return 0;
    }
};

class NumberExpression : public Expression {
    std::string numberString;
public:
    NumberExpression(const std::string &numberString) :
        numberString(numberString) {}
    int evaluate() override {
        return std::stoi(numberString);
    }
};

int main (int argc, const char *argv[]) {
    NumberExpression *num1 = new NumberExpression("45");
    NumberExpression *num2 = new NumberExpression("37");
    OperationExpression *exp1 = new OperationExpression("plus", num1, num2);
    std::cout << "45 + 37: " << exp1->evaluate() << std::endl;
    
    NumberExpression *num3 = new NumberExpression("63");
    OperationExpression *exp2 = new OperationExpression("minus", num3, exp1);
    std::cout << "63 - (45 + 37) : " << exp2->evaluate() << std::endl;
    
    delete num1;
    delete num2;
    delete num3;
    delete exp1;
    delete exp2;
    return 0;
}
