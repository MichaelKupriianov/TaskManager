project(tests)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(model_tests model/TaskTest.cpp model/TaskManagerTest.cpp model/id/TaskIdTest.cpp
        model/id/IdGeneratorTest.cpp ../src/model/Task.h ../src/model/Task.cpp ../src/model/TaskManager.h
        ../src/model/TaskManager.cpp ../src/model/id/IdGenerator.h ../src/model/id/TaskId.h
        ../src/model/id/TaskId.cpp ../src/model/GeneralizedTask.cpp ../src/model/GeneralizedTask.h
        model/GeneralizedTaskTest.cpp)

target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(model_tests)

add_executable(ui_tests ../src/model/Task.h ../src/model/Task.cpp ../src/ui/step/Step.cpp ../src/ui/step/Step.h
        ../src/ui/machine/StepMachine.cpp ../src/ui/machine/StepMachine.h ../src/ui/context/Context.cpp
        ../src/ui/context/Context.h ../src/ui/step/StepAdd.cpp ../src/ui/step/StepAdd.h ../src/ui/factory/Factory.cpp
        ../src/ui/factory/Factory.h ../src/ui/input/Reader.cpp ../src/ui/input/Reader.h
        ../src/ui/step/SubStep.cpp ../src/ui/step/SubStep.h ../src/ui/step/StepEdit.cpp ../src/ui/step/StepEdit.h
        ui/context/ContextTest.cpp ui/factory/FactoryTest.cpp ../src/ui/input/Converter.cpp ../src/ui/input/Converter.h
        ../src/ui/context/SubContext.cpp ../src/ui/context/SubContext.h ../src/ui/factory/SubFactory.cpp
        ../src/ui/factory/SubFactory.h ../src/ui/step/TypeOfStep.h ../src/ui/machine/SubStepMachine.cpp
        ../src/ui/machine/SubStepMachine.h ui/context/SubContextTest.cpp ui/factory/SubFactoryTest.cpp
        ui/input/ConverterTest.cpp ../src/model/id/TaskId.h ../src/model/id/TaskId.cpp ../src/ui/machine/Command.h)

target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(ui_tests)

add_executable(controller_tests ../src/controller/Controller.h ../src/controller/Controller.cpp)

target_link_libraries(controller_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(controller_tests)
