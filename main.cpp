#include <sstream>
#include <vector>
#include <iterator>
#include <ctime>
#include "create_task.h"

void show_tasks(std::ifstream &read_file, std::string &filename);
time_t convert_string_to_time_t(std::string &expiry_string);
int convert_expiry_to_days(std::string  &expiry);
void delete_task(int id, std::ifstream &read_file, std::string &filename);

int main(int argc, char **argv)
{
    std::string filename = "C:\\Users\\marcr\\CLionProjects\\todo\\cmake-build-debug\\todo storage.txt";
    std::ifstream read_file;
    std::ofstream append_file;

    if(argc == 1){
        show_tasks(read_file, filename);
        return 1;
    }
    else if(argc > 4){
        std::cout << "\nToo many command line arguments";
        return -1;
    }
    else{
        if(std::string(argv[1]) == "-a" && argc == 4){
            std::string expiry_date = argv[3];
            time_t expiry = convert_string_to_time_t(expiry_date);
            create_task task(argv[2], expiry);
            task.save_task(append_file, filename);
            show_tasks(read_file, filename);
        }
        else if(std::string(argv[1]) == "-a" && argc == 3){
            create_task task(argv[2]);
            task.save_task(append_file, filename);
            show_tasks(read_file, filename);
        }
        else if(std::string(argv[1]) == "-r" && argc == 3){
            delete_task(atoi(argv[2]), read_file, filename);
            show_tasks(read_file, filename);
        }
        else{
            std::cout << "\nIncorrect command line arguments";
            return -1;
        }
    }

    return 0;
}


void show_tasks(std::ifstream &read_file, std::string &filename)
{
    read_file.open(filename.c_str());
    if(!(read_file.is_open())){
        std::cout << "\nError opening file.";
    }
    std::string line;
    for(int i = 1; getline(read_file, line); i++){
        std::vector <std::string> tokens;
        std::stringstream check(line);
        std::string item;
        while (getline(check, item, '\"')) {
            tokens.push_back(item);
        }
        std::cout << i << ") ";
        std::cout << tokens[1] << " ";
        int days_left = convert_expiry_to_days(tokens[3]);
        if (tokens[3] != "0"){
            std::cout << "(" << days_left << " days left)" << std::endl;
        }
        else{
            std::cout << std::endl;
        }
    }

    read_file.close();
}

int convert_expiry_to_days(std::string &expiry)
{
    long int t = std::stol(expiry.c_str());
    time_t now = time(0);
    unsigned int current = static_cast<unsigned int>(now);
    return (t - current)/(86400);
}

time_t convert_string_to_time_t(std::string &expiry_string)
{
    struct tm expiry_struct = {0};
    int yy, mm, dd, days;
    const char *expiry_ptr = expiry_string.c_str();

    if(std::sscanf(expiry_ptr, "%d/%d/%d", &dd, &mm, &yy) == 3){
        expiry_struct.tm_year = yy - 1900;
        expiry_struct.tm_mon = mm - 1;
        expiry_struct.tm_mday = dd;
    }
    else {
        days = atoi(expiry_ptr);
        if(days <= 0){
            std::cout << std::endl << "Error reading in expiry date" << std::endl;
            return -1;
        }
        else{
            return time_t(days*86400) + time(0);
        }
    }

    return std::mktime(&expiry_struct);
}

void delete_task(int id, std::ifstream &read_file, std::string &filename)
{
    std::ofstream temp_file;
    std::string temp_path = "C:\\Users\\marcr\\CLionProjects\\todo\\cmake-build-debug\\temp.txt";
    temp_file.open(temp_path.c_str(), std::ios::out);
    if(temp_file.is_open()){
        read_file.open(filename.c_str());
        if(read_file.is_open()){
            std::string line;

            for(int i = 0; getline(read_file, line); i++){
                if (i + 1 != id)
                    temp_file << line << std::endl;
            }

            temp_file.close();
            read_file.close();
            std::remove(filename.c_str());
            std::rename(temp_path.c_str(), filename.c_str());
        }
    }
    else{
        std::cout << std::endl << "Error Creating temporary file" <<std::endl;
    }
}