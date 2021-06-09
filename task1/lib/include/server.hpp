#pragma once

#include "workingWithStudents.hpp"

class Server : public workingWithStudents {
public:
    bool addStudentsFromFile(std::string path);
    bool unifyList();
    bool sendZmq();
};