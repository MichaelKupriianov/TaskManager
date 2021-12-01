cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/model/)
include_directories(src/model/id)
include_directories(src/controller/)
include_directories(src/ui/)
include_directories(src/ui/step/)
include_directories(src/ui/input/)
include_directories(src/ui/factory/)
include_directories(src/ui/context/)
include_directories(src/ui/machine/)

add_executable(TaskManager src/main.cpp src/model/Task.cpp src/model/Task.h src/model/TaskManager.cpp
        src/model/TaskManager.h src/model/id/TaskId.cpp src/model/id/TaskId.h src/model/id/IdGenerator.h
        src/model/GeneralizedTask.cpp src/model/GeneralizedTask.h src/ui/step/Step.cpp src/ui/step/Step.h
        src/ui/machine/StepMachine.cpp src/ui/machine/StepMachine.h src/ui/context/Context.cpp src/ui/context/Context.h
        src/ui/step/StepAdd.cpp src/ui/step/StepAdd.h src/ui/factory/Factory.cpp src/ui/factory/Factory.h
        src/ui/input/Reader.cpp src/ui/input/Reader.h src/ui/step/SubStep.cpp src/ui/step/SubStep.h
        src/ui/step/StepEdit.cpp src/ui/step/StepEdit.h src/ui/input/Converter.cpp src/ui/input/Converter.h
        src/ui/context/SubContext.cpp src/ui/context/SubContext.h src/ui/factory/SubFactory.cpp src/ui/factory/SubFactory.h
        src/ui/step/TypeOfStep.h src/ui/machine/SubStepMachine.cpp src/ui/machine/SubStepMachine.h
        src/controller/Controller.cpp src/controller/Controller.h src/ui/machine/Command.h src/ui/input/Printer.cpp
        src/ui/input/Printer.h)
add_subdirectory(tests)