#include <string>
#include <iostream>

#include "client.hpp"

int main() {
    Client client;
    client.getFromServerZmq();
    client.sortList();
    for(auto &str: client.getListOfStudents()){
        std::cout << str << std::endl;
    }
    return 0;
}
