cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS src/persistent/*.proto)
message("PROTO_SOURCES ${PROTO_SOURCES}")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(proto_src proto_hdr src/api/Task.proto)
message("${proto_hdr}")

include_directories(src/)
include_directories(src/ui/)
include_directories(tests/)

file(GLOB_RECURSE API src/api/*)
file(GLOB_RECURSE Model src/model/*)
file(GLOB_RECURSE UI src/ui/*)
file(GLOB_RECURSE Persistence src/persistence/*)

add_executable(TaskManager ${proto_src} ${proto_hdr} ${API} ${Model} ${UI} ${Persistence} src/main.cpp)

target_link_libraries(TaskManager ${Protobuf_LIBRARIES})


file(GLOB_RECURSE model_tests_src CONFIGURE_DEPENDS
        "src/persistence/*.h"
        "model/*.cpp"
        )

add_executable(model_tests ${proto_src} ${proto_hdr} ${model_tests_src} ${Model} ${API})
target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(model_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(model_tests)


add_executable(persistence_tests ${proto_src} ${proto_hdr} ${Persistence} ${API} tests/persistence/PersisterTest.cpp)
target_link_libraries(persistence_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(persistence_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(persistence_tests)


file(GLOB_RECURSE ui_tests_src CONFIGURE_DEPENDS
        "src/model/*.h"
        "src/persistence/*.h"
        "ui/*.cpp"
        "ui/*.h"
        )

add_executable(ui_tests ${proto_src} ${proto_hdr} ${ui_tests_src} ${UI} ${API})
target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(ui_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(ui_tests)


add_executable(integration_tests ${proto_src} ${proto_hdr} ${API} ${Model} ${Persistence} ${UI} tests/MainTest.cpp)
target_link_libraries(integration_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(integration_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(integration_tests)