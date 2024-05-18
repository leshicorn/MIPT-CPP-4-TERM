/*Задача:
    Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков:
    Метод PerformPersonTasks должен реализовывать следующий алгоритм:
    1. Рассмотрим все не выполненные задачи разработчика person.
    2. Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи в статусе
IN_PROGRESS и, наконец, задачи в статусе TESTING.
    3. Рассмотрим первые task_count задач и переведём каждую из них в следующий статус в соответствии с естественным порядком: NEW→ IN_PROGRESS→ TESTING→ DONE.
    4. Вернём кортеж из двух элементов: информацию о статусах обновившихся задач(включая те,
    которые оказались в статусе DONE) и информацию о статусах остальных не выполненных задач.
Гарантируется, что task_count является положительным числом.Если task_count превышает текущее
количество невыполненных задач разработчика, достаточно считать, что task_count равен количеству
невыполненных задач: дважды обновлять статус какой - либо задачи в этом случае не нужно.
Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
Замечание:
    Обновление словаря одновременно с итерированием по нему может привести к непредсказуемым последствиям.При возникновении такой необходимости рекомендуется сначала в отдельном
временном словаре собрать информацию об обновлениях, а затем применить их к основному словарю.*/

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,
    // новая
    IN_PROGRESS, // в разработке
    TESTING,
    // на тестировании
    DONE
    // завершена
};
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map < TaskStatus, int > ;
class TeamTasks {
    public:
        // Получить статистику по статусам задач конкретного разработчика
        const TasksInfo & GetPersonTasksInfo(const string & person) const {
            
        }
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string & person) {

    }
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple < TasksInfo, TasksInfo > PerformPersonTasks(const string & person, int task_count);
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

    return 0;
}