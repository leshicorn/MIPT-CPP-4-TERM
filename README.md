В этой задаче мы воспользуемся умным указателем unique_ptr для управления временем
жизни дерева полиморфных объектов. А конкретнее, будем работать с деревом арифметического вы-
ражения. Узлами дерева будут числа и операции.
Например, выражение "2*(3+4)" будет представлено вот таким деревом:
*
| \
2  +
  / \
 3   4

В программе узлы дерева представляются объектами типов, унаследованных от интерфейса
Expression, который объявлен в файле Common.h. У интерфейса есть два метода:
• Evaluate() возвращает численное значение выражения. Для нашего примера это будет 14.
• ToString() форматирует выражение как строку. Для простоты реализации, чтобы не учитывать
приоритеты операций, каждый узел берётся в скобки. То есть для нашего примера этот метод
вернёт "(2)*((3)+(4))".

Так как Expression — это абстрактный класс, работать с ним можно только через указатель или
ссылку. Чтобы не заниматься ручным управлением памятью, будем использовать умный указатель
unique_ptr. Чтобы не загромождать код выражениями unique_ptr<Expression>, в файле Common.h для
этого выражения предоставлен синоним ExpressionPtr.
Реализуйте функции, которые позволяют создавать такое дерево выражения. Они объявлены
в файле Common.h, который приведён ниже:

Value() возвращает дерево из одного узла, представляющего целое число.
Sum() возвращает новое дерево, которое представляет сумму двух переданных выражений.
Product() возвращает новое дерево, которое представляет произведение двух переданных
выражений.
Таким образом, следующий код создаст дерево для выражения "2*(3+4)":

Product(Value(2), Sum(Value(3), Value(4)));

#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
    public: virtual~Expression() =
        default;

    // Вычисляет значение выражения
    virtual int Evaluate() const = 0;

    // Форматирует выражение как строку
    // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr < Expression > ;

// Функции для формирования выражения
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);

#include "Common.h"
#include <sstream>
using namespace std;

// Функция для проверки 
bool check_equal(string value1, string value2) {

}

string Print(const Expression * e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e -> ToString() << " = " << e -> Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    if !check_equal(Print(e1.get()), "(2)*((3)+(4)) = 14") {
        cout << "Error\n";
    }

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    if !check_equal(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19"){
        cout << "Error\n";
    }

    if !check_equal(Print(e1.get()), "Null expression provided"){
        cout << "Error\n";
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}
