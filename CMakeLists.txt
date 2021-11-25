cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/model/)
include_directories(src/ui/)
include_directories(src/ui/step/)
include_directories(src/ui/input/)

add_executable(TaskManager src/main.cpp src/model/Task.cpp src/model/Task.h src/model/TaskManager.cpp
        src/model/TaskManager.h src/model/id/TaskId.cpp src/model/id/TaskId.h src/model/id/IdGenerator.h
        src/model/GeneralizedTask.cpp src/model/GeneralizedTask.h src/ui/step/Step.cpp src/ui/step/Step.h
        src/ui/StepMachine.cpp src/ui/StepMachine.h src/ui/Context.cpp src/ui/Context.h src/ui/step/StepAdd.cpp
        src/ui/step/StepAdd.h src/ui/Factory.cpp src/ui/Factory.h src/ui/input/ConsoleManager.cpp
        src/ui/input/ConsoleManager.h src/ui/step/SubStep.cpp src/ui/step/SubStep.h src/ui/step/StepEdit.cpp
        src/ui/step/StepEdit.h src/ui/input/Validator.cpp src/ui/input/Validator.h)
add_subdirectory(tests)