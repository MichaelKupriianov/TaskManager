cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskManager src/main.cpp src/model/Task.cpp src/model/Task.h src/model/TaskManager.cpp src/model/TaskManager.h src/model/id/TaskId.cpp src/model/id/TaskId.h src/model/id/IdGenerator.h)
