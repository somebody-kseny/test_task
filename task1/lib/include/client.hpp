#pragma once

#include "workingWithStudents.hpp"

class Client : public workingWithStudents{
public:
    bool getFromServerZmq();
    bool sortList();
};