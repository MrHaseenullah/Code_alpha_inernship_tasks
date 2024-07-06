#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Task class to represent a task
class Task {
private:
    string name;
    string description;
    bool completed;

public:
    Task(const string& name, const string& desc) : name(name), description(desc), completed(false) {}

    void markCompleted() 
    {
        completed = true;
    }

    string getName() const 
    {
        return name;
    }

    string getDescription() const 
    {
        return description;
    }

    bool isCompleted() const 
    {
        return completed;
    }
};

// TaskManager class to manage tasks
class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const string& name, const string& description) 
    {
        tasks.emplace_back(name, description);
        cout << "Task added.\n";
    }

    void markCompleted(int index) 
    {
        if (index >= 0 && index < tasks.size()) 
        {
            tasks[index].markCompleted();
            cout << "Task marked as completed.\n";
        } else 
        {
            cout << "Invalid task index.\n";
        }
    }

    void displayTasks() const 
    {
        if (tasks.empty()) 
        {
            cout << "No tasks available.\n";
            return;
        }

        cout << "Current Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) 
        {
            cout << i + 1 << ". ";
            if (tasks[i].isCompleted()) 
            {
                cout << "[✔] ";
            } else {
                cout << "[X] ";
            }
            cout << tasks[i].getName() << ": " << tasks[i].getDescription() << endl;
        }
    }

    bool isTasksEmpty() const 
    {
        return tasks.empty();
    }
};

int main() {
    TaskManager taskManager;
    string name, description;
    int choice;

    cout << "Simple To-Do Application\n\n";

    while (true) 
    {
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. View Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear input buffer

        switch (choice) 
        {
            case 1:
                cout << "Enter task name: ";
                getline(cin, name);
                cout << "Enter task description: ";
                getline(cin, description);
                taskManager.addTask(name, description);
                break;
            case 2:
                if (taskManager.isTasksEmpty()) 
                {
                    cout << "No tasks available.\n";
                } else {
                    int index;
                    cout << "Enter task index to mark as completed: ";
                    cin >> index;
                    taskManager.markCompleted(index - 1); // Convert to 0-based index
                }
                break;
            case 3:
                taskManager.displayTasks();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
        cout << endl; // Provide spacing between operations
    }

    return 0;
}
