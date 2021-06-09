#pragma once

struct Student {
    int num;
    std::string name;
    std::string surname;
    std::string dateOfBirth;
    bool operator==(Student& given) const{
        if ( this->name == given.name && this->surname == given.surname && this->dateOfBirth == given.dateOfBirth){
            return true;
        }
        return false;
    };

    bool operator()(const Student& first, const Student& second) const{
        if (first.surname > second.surname){
            return true;
        }
        if (first.surname == second.surname && first.name > second.name){
            return true;
        }
        return false;
    }
};
