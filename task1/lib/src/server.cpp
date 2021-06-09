#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>

#include "server.hpp"
#include "zmq.h"

#define AMOUNT_OF_SENDS 10

bool Server::sendZmq() {
    void* context = zmq_ctx_new();
    void* publisher = zmq_socket(context, ZMQ_PUB);
//    printf("Starting server...\n");
    int conn = zmq_bind(publisher, "tcp://*:4040");

    int index = 8;
    char* update = new char[index];
    int counter = 0;
    zmq_msg_t message;
    std::string amount = "amount";
    while(counter < AMOUNT_OF_SENDS) {
        amount += std::to_string(students.size()) + "|";
        index = (int)amount.length()+1;
        update = new char[index];
        snprintf(update, sizeof(char)*index, "%s", amount.c_str());
        zmq_msg_init_size(&message, index);
        memcpy(zmq_msg_data(&message), update, index);
        zmq_msg_send(&message, publisher, 0);
        zmq_msg_close(&message);
        delete[] update;

        for(auto msg : getListOfStudents()) {
            index = (int)msg.length()+1;
            update = new char[index];
            snprintf(update, sizeof(char)*index, "%s", msg.c_str());
            zmq_msg_init_size(&message, index);
            memcpy(zmq_msg_data(&message), update, index);
            zmq_msg_send(&message, publisher, 0);
            zmq_msg_close(&message);
            delete[] update;
        }

        counter++;
        sleep(1);
    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return true;
}

bool Server::addStudentsFromFile(std::string path) {
    std::ifstream fileInput;
    fileInput.open(path);
    if (!fileInput.is_open()) {
        return false;
    }
    std::string str;
    Student student;
    while (fileInput >> student.num >> student.name >> student.surname >> student.dateOfBirth){
        //list.push_back(str);
        students.push_back(student);
    }
    return true;
}

bool Server::unifyList() {
    if(students.empty()) {
        return false;
    }
    for(int i = 0; i < students.size(); i++){
        for(int j = i+1; j < students.size(); j++){
            if(students[i] == students[j]){
                students.erase(students.begin()+j);
                j--;
            }
        }
    }
    int i = 1;
    for(auto &student: students){
        student.num = i;
        i++;
    }
    return true;
}
