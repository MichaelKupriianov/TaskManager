cmake_minimum_required(VERSION 3.20)
project(TaskManager)
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(proto_src proto_hdr src/api/Task.proto)
message("${proto_hdr}")

include_directories(src)
include_directories(tests)

file(GLOB_RECURSE model_src src/model/* src/api/* src/persistence/*)
file(GLOB_RECURSE ui_src src/ui/* src/api/* src/model/*.h src/persistence/*.h)
file(GLOB_RECURSE model_tests_src "tests/model/*" "tests/persistence/*")
file(GLOB_RECURSE ui_tests_src "tests/ui/*")

add_executable(TaskManager ${proto_src} ${proto_hdr} ${model_src} ${ui_src} src/main.cpp)
target_link_libraries(TaskManager ${Protobuf_LIBRARIES})

add_executable(model_tests ${proto_src} ${proto_hdr} ${model_src} ${model_tests_src})
target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(model_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(model_tests)

add_executable(ui_tests ${proto_src} ${proto_hdr} ${ui_src} ${ui_tests_src})
target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(ui_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(ui_tests)

add_executable(integration_tests ${proto_src} ${proto_hdr} ${model_src} ${ui_src} tests/IntegrationTest.cpp)
target_link_libraries(integration_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(integration_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(integration_tests)