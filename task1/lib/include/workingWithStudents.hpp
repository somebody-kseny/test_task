#pragma once

#include <vector>
#include <string>

#include "student.hpp"

class workingWithStudents {
public:
    std::vector<std::string> getListOfStudents();
protected:
    std::vector<Student> students;
};
