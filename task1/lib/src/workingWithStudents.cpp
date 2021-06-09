#include "workingWithStudents.hpp"

std::vector <std::string> workingWithStudents::getListOfStudents() {
    std::vector<std::string> res;
    std::string str;
    for (auto &student: students){
        str += std::to_string(student.num) + " ";
        str += student.name + " ";
        str += student.surname + " ";
        str += student.dateOfBirth;
        res.push_back(str);
        str.clear();
    }
    return res;
}
