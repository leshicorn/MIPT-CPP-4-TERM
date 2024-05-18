task1:
#include <iostream>
#include <string>
#include <map>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW, // новая
    IN_PROGRESS, // в разработке
    TESTING, // на тестировании
    DONE // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>, позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks_.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person) {
        tasks_[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated, untouched;

        TasksInfo& person_tasks = tasks_[person];

        // Сначала посчитаем все невыполненные задачи
        int new_count = person_tasks[TaskStatus::NEW];
        int in_progress_count = person_tasks[TaskStatus::IN_PROGRESS];
        int testing_count = person_tasks[TaskStatus::TESTING];

        // Начнем обновление статусов
        while (task_count > 0 && new_count > 0) {
            updated[TaskStatus::IN_PROGRESS]++;
            new_count--;
            task_count--;
        }
        while (task_count > 0 && in_progress_count > 0) {
            updated[TaskStatus::TESTING]++;
            in_progress_count--;
            task_count--;
        }
        while (task_count > 0 && testing_count > 0) {
            updated[TaskStatus::DONE]++;
            testing_count--;
            task_count--;
        }

        // Обновляем исходные данные для разработчика
        person_tasks[TaskStatus::NEW] = new_count;
        person_tasks[TaskStatus::IN_PROGRESS] += updated[TaskStatus::IN_PROGRESS] - in_progress_count;
        person_tasks[TaskStatus::TESTING] += updated[TaskStatus::TESTING] - testing_count;
        person_tasks[TaskStatus::DONE] += updated[TaskStatus::DONE];

        // Формируем информацию о не обновленных задачах
        if (new_count > 0) untouched[TaskStatus::NEW] = new_count;
        if (in_progress_count > 0) untouched[TaskStatus::IN_PROGRESS] = in_progress_count;
        if (testing_count > 0) untouched[TaskStatus::TESTING] = testing_count;

        // Удаляем нулевые записи
        for (auto& [status, count] : person_tasks) {
            if (count == 0) {
                person_tasks.erase(status);
            }
        }

        return {updated, untouched};
    }

private:
    map<string, TasksInfo> tasks_;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    
    PrintTasksInfo(untouched_tasks);




task 2:
// Common.h

#pragma once

#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual int Evaluate() const = 0;

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// Функции для формирования выражения
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);

#include <sstream>

using namespace std;

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
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}





file2task2:








// main.cpp

#include "Common.h"
#include <iostream>
#include <sstream>
#include <cassert>

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

// Реализация функций создания узлов дерева
ExpressionPtr Value(int value) {
  return make_unique<ValueNode>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
  return make_unique<SumNode>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
  return make_unique<ProductNode>(move(left), move(right));
}

// Тесты
void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  assert(Print(e1.get()) == "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  assert(Print(e2.get()) == "((2)*((3)+(4)))+(5) = 19");

  assert(Print(e1.get()) == "Null expression provided");
}

int main() {
  Test();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}









    
