//
// Created by marcr on 14/11/2018.
//

#include "create_task.h"

create_task::create_task(char* n, char* d)
{
    name = n;
    expiry = 0;
    description = d;
}

create_task::create_task(char* n, char* d, time_t e)
{
    name = n;
    expiry = e;
    description = d;
}

void create_task::save_task(std::ifstream &read_file, std::string filename)
{
    std::cout << std::endl << "Creating new task...";

    std::ofstream temp_file;
    std::string temp_path = "C:\\Users\\marcr\\CLionProjects\\todo\\cmake-build-debug\\temp.json";
    temp_file.open(temp_path.c_str(), std::ios::out);
    if(temp_file.is_open()) {
        read_file.open(filename.c_str());
        if (read_file.is_open()) {
            std::cout << "\nReading in tasks\n";
            json tasks = json::parse(read_file);

            // Add a task to tasks object
            int index = tasks.size();
            tasks[index]["Name"] = name;
            tasks[index]["Description"] = description;
            tasks[index]["Expiry"] = expiry;

            temp_file << std::setw(4) << tasks;
        }

        temp_file.close();
        read_file.close();
        std::remove(filename.c_str());
        std::rename(temp_path.c_str(), filename.c_str());
    }
    else{
        std::cout << std::endl << "Error Creating temporary file" <<std::endl;
    }
}
