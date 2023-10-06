#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    string title;
    string description;
    string dueDate;
    bool completed;

    Task(string t, string d, string dd) : title(t), description(d), dueDate(dd), completed(false) {}
};

class TaskTracker {
private:
    vector<Task> tasks;
    string filename = "tasks.txt";

public:
    void loadTasksFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string title, description, dueDate;
            bool completed;
            while (file >> title >> description >> dueDate >> completed) {
                tasks.emplace_back(title, description, dueDate);
                tasks.back().completed = completed;
            }
            file.close();
        }
    }

    void saveTasksToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.title << " " << task.description << " " << task.dueDate << " " << task.completed << "\n";
            }
            file.close();
        }
    }

    void addTask(string title, string description, string dueDate) {
        tasks.emplace_back(title, description, dueDate);
    }

    void displayTasks() {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". ";
            cout << "Title: " << tasks[i].title << endl;
            cout << "Description: " << tasks[i].description << endl;
            cout << "Due Date: " << tasks[i].dueDate << endl;
            cout << "Status: " << (tasks[i].completed ? "Completed" : "Pending") << endl;
            cout << "--------------------------" << endl;
        }
    }

    //

    void editTask(size_t taskIndex, string title, string description, string dueDate) 
    {
        if (taskIndex >= 0 && taskIndex < tasks.size()) 
        {
            tasks[taskIndex].title = title;
            tasks[taskIndex].description = description;
            tasks[taskIndex].dueDate = dueDate;
        }
    }

    // deletes tasks

    void deleteTask(size_t taskIndex) 
    {
        if (taskIndex >= 0 && taskIndex < tasks.size()) 
        {
            tasks.erase(tasks.begin() + taskIndex);
        }
    }

    // marks tasks as complete

    void markTaskAsCompleted(size_t taskIndex) 
    {
        if (taskIndex >= 0 && taskIndex < tasks.size()) 
        {
            tasks[taskIndex].completed = true;
        }
    }

    // sorts list by date

    void sortTasksByDueDate() 
    {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) 
        {
            return a.dueDate < b.dueDate;
        });
    }

    // sorts list by status

    void sortTasksByStatus() 
    {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) 
        {
            return a.completed > b.completed;
        });
    }

    // Check if there are any tasks

    bool hasTasks() 
    {
        if (tasks.empty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

int main() {
    TaskTracker taskTracker;
    taskTracker.loadTasksFromFile();

    // Menu interface to select action to perform on tasks

    int choice;
    while (true) {
        cout << "Task Tracker Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. View Tasks\n";
        cout << "6. Sort Tasks by Due Date\n";
        cout << "7. Sort Tasks by Status\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        // switch through different menu options

        switch (choice) {
            case 1: {
                string title, description, dueDate;
                cout << "Enter task title: ";
                getline(cin, title);
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter due date (YYYY-MM-DD): ";
                getline(cin, dueDate);
                taskTracker.addTask(title, description, dueDate);
                break;
            }
            case 2: {
                size_t index;
                string title, description, dueDate;
                cout << "Enter the task number to edit: ";
                cin >> index;
                cin.ignore();
                --index; // Adjust index to match vector indexing
                cout << "Enter new task title: ";
                getline(cin, title);
                cout << "Enter new task description: ";
                getline(cin, description);
                cout << "Enter new due date (YYYY-MM-DD): ";
                getline(cin, dueDate);
                taskTracker.editTask(index, title, description, dueDate);
                break;
            }
            case 3: {
                if (taskTracker.hasTasks() == true)
                {
                    size_t index;
                    cout << "Enter the task number to delete: ";
                    cin >> index;
                    --index;
                    taskTracker.deleteTask(index);
                    break;
                }
            }
            case 4: {
                size_t index;
                cout << "Enter the task number to mark as completed: ";
                cin >> index;
                --index;
                taskTracker.markTaskAsCompleted(index);
                break;
            }
            case 5:
                taskTracker.displayTasks();
                break;
            case 6:
                taskTracker.sortTasksByDueDate();
                break;
            case 7:
                taskTracker.sortTasksByStatus();
                break;
            case 8:
                taskTracker.saveTasksToFile();
                cout << "Tasks saved. Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}