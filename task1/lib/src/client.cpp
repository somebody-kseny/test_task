#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "client.hpp"
#include "zmq.h"

bool Client::getFromServerZmq() {
    void* context = zmq_ctx_new();
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    int conn = zmq_connect(subscriber, "tcp://localhost:4040");
    conn = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, 0, 0);
    char* value;
    // получение количества строк
    int amountOfRes = -1;
    zmq_msg_t reply;
    while (amountOfRes < 0) {
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, subscriber, 0);
        size_t length = zmq_msg_size(&reply);
        value = new char [length];
        memcpy(value, zmq_msg_data(&reply), length);
        zmq_msg_close(&reply);
        int i = 0;
        std::string amount = "amount";
        for(auto c: amount){
            if( *(value+i) != c ) {
                break;
            }
            ++i;
        }
        if(i == amount.length()){
            amountOfRes = std::stoi(value+i);
        }
    }

    // получение самих строк
    Student student;
    for (int i = 0; i < amountOfRes; i++){
        //zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, subscriber, 0);
        size_t length = zmq_msg_size(&reply);
        value = new char [length];
        memcpy(value, zmq_msg_data(&reply), length);
        zmq_msg_close(&reply);
        std::istringstream stringIS(value);
        stringIS >> student.num >> student.name >> student.surname >> student.dateOfBirth;
        students.push_back(student);
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return true;
}

bool Client::sortList() {
    std::sort(std::begin(students), std::end(students), Student());
    int i = 1;
    for(auto &student: students){
        student.num = i;
        i++;
    }
    return true;
}
