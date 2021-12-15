#pragma once

#include<iostream>
#include"Task.pb.h"

class Holder {
public:
    void Save() {
        Task task;
        task.set_title("reg");
        std::cout<<task.title();



    }
    void Load() {



    }
};

