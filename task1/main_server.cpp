#include <string>
#include <iostream>
#include <zmq.h>
#include <vector>
#include <cstring>
#include <unistd.h>

#include "server.hpp"

int main() {
    Server server;
    server.addStudentsFromFile("../files/student_file_1.txt");
    server.addStudentsFromFile("../files/student_file_2.txt");
    server.unifyList();
    server.sendZmq();
    return 0;
}
