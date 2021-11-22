project(tests)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(all_tests model/TaskTest.cpp model/TaskManagerTest.cpp model/id/TaskIdTest.cpp model/id/IdGeneratorTest.cpp
        ../src/model/Task.h ../src/model/Task.cpp ../src/model/TaskManager.h ../src/model/TaskManager.cpp
        ../src/model/id/IdGenerator.h ../src/model/id/TaskId.h ../src/model/id/TaskId.cpp ../src/model/GeneralizedTask.cpp ../src/model/GeneralizedTask.h model/GeneralizedTaskTest.cpp)

target_link_libraries(all_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(all_tests)