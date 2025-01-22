#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h> 

using namespace std;

// class SubTask {
//     private:
//         string title;
//         string description;
//         bool completed;

    
//     public:
//         string getTitle() const { return title; }
//         string getDescription() const { return description; }
//         bool isCompleted() const { return completed; }

// };

class Task {

    private:
        string title;
        string description;
        bool completed;
        // vector<SubTask> subtasks;
    
    public:
        Task(const string& title, const string& description): 
            title(title), description(description), completed(false) {}

        // Getter funcs
        string getTitle() const { return title; }
        string getDescription() const { return description; }
        bool isCompleted() const { return completed; }
        // vector<SubTask> getSubTasks() const { return  subtasks; }
        // bool hasSubTasks() const { return subtasks.empty(); }

        // Setter funcs
        void setTitle(const string& title) { this->title = title; }
        void setDescription(const string& description) { this->description = description; }
        void markComplete() { this->completed = true; }
        void printTask() const {
            cout << " [" << (completed ? "X": " ") << "] " << title  << endl;
            cout << "      ↳ Description: " << description << endl;
        }
        
};


class TaskList {
    private:
        string title;
        vector<Task> tasks;
    
    public:
        TaskList(const string& title): 
            title(title) {}
        
        // Getter funcs
        string getTitle() const { return title; }
        vector<Task> getTasks() const { return tasks; }

        // Setter funcs
        void setTitle(const string& title) { this->title = title; }

        void addTask(string title) {
            string description;

            cout << "Enter task description: ";
            getline(cin, description);

            tasks.emplace_back(title, description);
            cout << "Task added successfully." << endl;
        }

        void deleteTask(string title) {
            if (tasks.empty()) {
                cout << "No tasks to delete...." << endl;
                return;
            }

            bool found_task = false;
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i].getTitle() == title) {
                    found_task = true;
                    tasks.erase(tasks.begin() + i);
                    cout << "Task deleted successfully!" << endl;
                    break;
                }
            }
            
            if (!found_task) {
                cout << "No task found with the specified name..." << endl;
            }
        }

        void markCompleted(string title) {

            if (tasks.empty()) {
                cout << "No tasks..." << endl;
                return;
            }

            bool found_task = false;
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i].getTitle() == title) {
                    found_task = true;
                    tasks[i].markComplete();
                    cout << "Task completed successfully!" << endl;
                    break;
                }
                
            }

            if (!found_task) {
                cout << "No task found with the specified name..." << endl;
            }
        }

        
        void editTask(string title) {
            if (tasks.empty()) {
                cout << "No tasks to edit...." << endl;
                return;
            }

            bool found_task = false;
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i].getTitle() == title) {
                    found_task = true;
                    string new_title, new_description;

                    cout << "Enter new task title (leave blank/hit enter key if no change): ";
                    getline(cin, new_title);
                    // if (new_title.size())
                    if (new_title.size() != 0) { 
                        tasks[i].setTitle(new_title);
                        cout << "Task title updated successfully!" << endl;
                    } else {
                        cout << "Title unchanged..." << endl;
                    }
                    
                    cout << "Enter new task description (leave blank/hit enter key if no change): ";
                    getline(cin, new_description);
                    if (new_description.size() != 0) {
                        tasks[i].setDescription(new_description);
                        cout << "Task description updated successfully!" << endl;
                    } else {
                        cout << "Description unchanged..." << endl;
                    }
                    break;
                }
            }
            
            if (!found_task) {
                cout << "No task found with the specified name..." << endl;
            }
        }
    
        // void showTasks() {
        //     if (tasks.empty()) {
        //         cout << "No tasks" << endl;
        //         return;
        //     }

        //     cout << "Tasks" << endl;
        // }

};


class ToDo {
    private:
        vector<TaskList> tasklists;
        // TaskList activelist; // maybe store pointer instead if implementing this??
    
    public:

        // vector<TaskList> getTaskLists() const { return tasklists; }
        // void setActiveList(TaskList selected_list) { this->activelist = selected_list; }


        void run() {

            cout << u8"\033[2J\033[1;1H";
            cout << "/*****************************************/\n";
            cout << "      Welcome To Do Terminal (TDT)\n";
            cout << "    Type \"help\" for a list of commands\n";
            cout << "/*****************************************/\n";


            string cmd, cmd_split;
            vector <string> cmd_args;
            bool running = true;

            vector <Task> tasklist_tasks;
            bool found_tasklist = false;

            do {
                cout << "> ";

                getline(cin, cmd);
                stringstream cmd_stream(cmd);
                while (getline(cmd_stream, cmd_split, ' ')) {
                    // cout << cmd_split << endl;
                    cmd_args.emplace_back(cmd_split);
                }

                int cmd_args_size = cmd_args.size();
                cmd_args[0] = cmd_args[0];
                if (cmd_args[0] == string ("help")) {
                    cout << "Available commands: " << endl;
                    cout << "  * help: display this list\n";
                    cout << "  * ls: list tasks\n";
                    cout << "  * newtl: create new task list\n";
                    cout << "  * addto: add a task\n";
                    cout << "  * del: delete a task\n";
                    cout << "  * edit: edit a task's description\n";
                    cout << "  * complete: mark a task as completed\n";
                    cout << "  * rename: rename a task\n";
                    cout << "  * clear: clear screen/terminal\n";
                    cout << "  * exit: close program\n";


                } else if (cmd_args[0] == string("ls")) {

                    if (tasklists.size() < 1) { 
                        cout << "No tasklists, create a new one with the newtl command" << endl;
                    
                    } else if (cmd_args_size > 1) {                        
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                tasklist_tasks = tasklists[i].getTasks();
                                for (int j = 0; j < tasklist_tasks.size(); j++) {
                                    tasklist_tasks[j].printTask();
                                }
                                break;
                            }
                        }

                        if (!found_tasklist) {
                            cout << "No tasklist with the specified name \"" << cmd_args[1] << "\", please check your current tasklists with the basic ls command" << endl;
                        }
                        
                    } else {
                        for (int i = 0; i < cmd_args_size; i++) {
                            cout << "  * " << tasklists[i].getTitle() << endl;
                        }
                    }
                    

                } else if (cmd_args[0] == string("newtl")){
                    cout << "Created new task list titled: " << cmd_args[1] << endl;
                    // example: > newtl name_of_tasklist
                    tasklists.emplace_back((string(cmd_args[1])));

                } else if (cmd_args[0] == string("addto")) {

                    if (tasklists.size() < 1) { cout << "No tasklists, create a new one with the newtl command" << endl; }
                    else if (cmd_args_size != 3) { cout << "Invalid use of add function" << endl; }
                    else {
                        
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                tasklists[i].addTask(cmd_args[2]);
                                break;
                            }
                        }   
                        if (!found_tasklist) {
                            cout << "No tasklist with the specified name \"" << cmd_args[1] << "\", please check your current tasklists with the ls command" << endl;
                        }
                    }

                } else if (cmd_args[0] == string("del")) {

                    if (tasklists.size() < 1) { cout << "No tasklists, create a new one with the newtl command" << endl; }

                    else if (cmd_args_size == 2) {    
                        // delete tasklist and all tasks associated
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                tasklists.erase(tasklists.begin() + i);
                                cout << "Task-list deleted..." << endl;
                                break;
                            }
                        }   

                    } else if (cmd_args_size == 3) {
                        // delete single task
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                tasklists[i].deleteTask(cmd_args[2]);
                                break;
                            }
                        }   
                        if (!found_tasklist) {
                            cout << "No tasklist with the specified name \"" << cmd_args[1] << "\", please check your current tasklists with the ls command" << endl;
                        }

                    } else {
                        cout << "Invalid use of del function" << endl;
                    }
                    

                } else if (cmd_args[0] == string("edit")) {

                    if (tasklists.size() < 1) { cout << "No tasklists, create a new one with the newtl command" << endl; }
                    else if (cmd_args_size != 3) { cout << "Invalid use of edit function" << endl; }
                    else {
                        
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                // tasklists[i].markCompleted(cmd_args[2]);
                                tasklists[i].editTask(cmd_args[2]);
                                break;
                            }
                        }   
                        if (!found_tasklist) {
                            cout << "No tasklist with the specified name \"" << cmd_args[1] << "\", please check your current tasklists with the ls command" << endl;
                        }
                    }

                } else if (cmd_args[0] == string("complete")) {
                    
                    if (tasklists.size() < 1) { cout << "No tasklists, create a new one with the newtl command" << endl; }
                    else if (cmd_args_size != 3) { cout << "Invalid use of complete function" << endl; }
                    else {
                        
                        for (int i = 0; i < cmd_args_size; i++) {
                            if (tasklists[i].getTitle() == cmd_args[1]) {
                                found_tasklist = true;
                                tasklists[i].markCompleted(cmd_args[2]);
                                break;
                            }
                        }   
                        if (!found_tasklist) {
                            cout << "No tasklist with the specified name \"" << cmd_args[1] << "\", please check your current tasklists with the ls command" << endl;
                        }
                    }

                } else if (cmd_args[0] == string("rename")) {
                    cout << "Rename task..." << endl;

                } else if (cmd_args[0] == string("clear")) {
                    cout << u8"\033[2J\033[1;1H";

                } else if (cmd_args[0] == string("exit")) {
                    cout << "Exiting..." << endl;
                    running = false;
                } else {
                    cout << "Invalid command, type \"help\" for a list of valid commands" << endl;
                }

                // reset variables
                found_tasklist = false;


                cmd_args.clear();
            } while (running);
            return;
        }
};


int main() {

    ToDo testing;
    testing.run();

    return 0;
}