//
// Created by marcr on 14/11/2018.
//

#ifndef TODO_CREATE_TASK_H
#define TODO_CREATE_TASK_H


#include <string>
#include <fstream>
#include <iostream>

class create_task {
private:
    char* name;
    time_t expiry;

public:
    explicit create_task(char* n);
    create_task(char* n, time_t e);
    void save_task(std::ofstream  &append_file, std::string filename);
};

#endif //TODO_CREATE_TASK_H
