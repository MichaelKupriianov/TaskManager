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
        ../src/ui/StepMachine.cpp ../src/ui/StepMachine.h ../src/ui/Context.cpp ../src/ui/Context.h
        ../src/ui/step/StepAdd.cpp ../src/ui/step/StepAdd.h ../src/ui/Factory.cpp ../src/ui/Factory.h
        ../src/ui/Reader.cpp ../src/ui/Reader.h ../src/ui/step/SubStep.cpp ../src/ui/step/SubStep.h ../src/ui/step/StepEdit.cpp ../src/ui/step/StepEdit.h)

target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(ui_tests)