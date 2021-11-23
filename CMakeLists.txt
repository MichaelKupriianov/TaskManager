cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/model/)
include_directories(src/ui/)
include_directories(src/ui/state/)

add_executable(TaskManager src/main.cpp src/model/Task.cpp src/model/Task.h src/model/TaskManager.cpp
        src/model/TaskManager.h src/model/id/TaskId.cpp src/model/id/TaskId.h src/model/id/IdGenerator.h
        src/model/GeneralizedTask.cpp src/model/GeneralizedTask.h src/ui/state/State.cpp src/ui/state/State.h
        src/ui/StateMachine.cpp src/ui/StateMachine.h src/ui/Context.cpp src/ui/Context.h src/ui/state/StateAdd.cpp
        src/ui/state/StateAdd.h src/ui/Factory.cpp src/ui/Factory.h src/ui/Reader.cpp src/ui/Reader.h)
add_subdirectory(tests)