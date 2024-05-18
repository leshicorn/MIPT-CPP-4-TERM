#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
private:
    map<string, TasksInfo> tasks; // Map to store tasks for each person

public:
    void AddNewTask(const string &person) {
        tasks[person][TaskStatus::NEW]++;
    }

    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return tasks.at(person);
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        TasksInfo &personTasks = tasks[person];
        TasksInfo updatedTasks, untouchedTasks;

        for (auto it = personTasks.begin(); it != personTasks.end(); ++it) {
            TaskStatus currentStatus = it->first;
            int &currentCount = it->second;

            if (task_count == 0) {
                untouchedTasks[currentStatus] = currentCount;
            } else {
                int tasksToProcess = min(task_count, currentCount);
                task_count -= tasksToProcess;

                TaskStatus nextStatus = static_cast<TaskStatus>(static_cast<int>(currentStatus) + 1);

                if (nextStatus != TaskStatus::DONE) {
                    updatedTasks[nextStatus] += tasksToProcess;
                }

                currentCount -= tasksToProcess;
                if (currentCount > 0) {
                    untouchedTasks[currentStatus] = currentCount;
                }
            }
        }

        // Clean up empty task statuses
        for (auto it = personTasks.begin(); it != personTasks.end();) {
            if (it->second == 0) {
                it = personTasks.erase(it);
            } else {
                ++it;
            }
        }

        return make_tuple(updatedTasks, untouchedTasks);
    }
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks, "
         << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress, "
         << tasks_info[TaskStatus::TESTING] << " tasks are being tested, "
         << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
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

    TasksInfo updatedTasks, untouchedTasks;
    tie(updatedTasks, untouchedTasks) = tasks.PerformPersonTasks("Ivan", 2);

    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updatedTasks);

    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouchedTasks);

    tie(updatedTasks, untouchedTasks) = tasks.PerformPersonTasks("Ivan", 2);

    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updatedTasks);

    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouchedTasks);

    return 0;
}
