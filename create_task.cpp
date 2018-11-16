//
// Created by marcr on 14/11/2018.
//

#include "create_task.h"

create_task::create_task(char* n)
{
    name = n;
    expiry = 0;
}

create_task::create_task(char* n, time_t e)
{
    name = n;
    expiry = e;
}

void create_task::save_task(std::ofstream  &append_file, std::string filename)
{
    append_file.open(filename.c_str(), std::ios::app);
    if(!(append_file.is_open())){
        std::cout << "File did not open\n";
    }
    append_file << "\"" << name << "\" " << "\""  << expiry << "\"" << std::endl;
    append_file.close();
}
