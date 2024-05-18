#include "Common.h"
#include <sstream>
#include <iostream>
#include <cassert>
using namespace std;

// Класс для представления числового значения
class ValueNode : public Expression {
public:
    explicit ValueNode(int value) : value_(value) {}

    int Evaluate() const override {
        return value_;
    }

    std::string ToString() const override {
        return std::to_string(value_);
    }

private:
    int value_;
};

// Класс для представления операции суммы
class SumNode : public Expression {
public:
    SumNode(ExpressionPtr left, ExpressionPtr right)
        : left_(move(left)), right_(move(right)) {}

    int Evaluate() const override {
        return left_->Evaluate() + right_->Evaluate();
    }

    std::string ToString() const override {
        return "(" + left_->ToString() + ")+(" + right_->ToString() + ")";
    }

private:
    ExpressionPtr left_, right_;
};

// Класс для представления операции произведения
class ProductNode : public Expression {
public:
    ProductNode(ExpressionPtr left, ExpressionPtr right)
        : left_(move(left)), right_(move(right)) {}

    int Evaluate() const override {
        return left_->Evaluate() * right_->Evaluate();
    }

    std::string ToString() const override {
        return "(" + left_->ToString() + ")*(" + right_->ToString() + ")";
    }

private:
    ExpressionPtr left_, right_;
};

// Реализация функций создания узлов дерева и операций над ними.
ExpressionPtr Value(int value) {
    return make_unique<ValueNode>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<SumNode>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<ProductNode>(move(left), move(right));
}

// Функция для проверки равенства строк
bool check_equal(string value1, string value2) {
    return value1 == value2;
}

string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    if (!check_equal(Print(e1.get()), "(2)*((3)+(4)) = 14")) {
        cout << "Error: " << Print(e1.get()) << " != (2)*((3)+(4)) = 14" << endl;
    }

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    if (!check_equal(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19")) {
        cout << "Error: " << Print(e2.get()) << " != ((2)*((3)+(4)))+(5) = 19" << endl;
    }

    if (!check_equal(Print(e1.get()), "Null expression provided")) {
        cout << "Error: " << Print(e1.get()) << " != Null expression provided" << endl;
    }
}

int main() {
    Test();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

