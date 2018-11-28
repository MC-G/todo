//
// Created by marcr on 14/11/2018.
//

#ifndef TODO_CREATE_TASK_H
#define TODO_CREATE_TASK_H

#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

class create_task {
private:
    char* name;
    char* description;
    time_t expiry;

public:
    explicit create_task(char* n, char* d);
    create_task(char* n, char* d, time_t e);
    void save_task(std::ifstream &read_file, std::string filename);
};

#endif //TODO_CREATE_TASK_H
