cmake_minimum_required(VERSION 3.20)
project(TaskManager)
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS proto/*.proto)
message("PROTO_SOURCES ${PROTO_SOURCES}")
set(PROTO_DIR ${TaskManager_SOURCE_DIR}/proto)
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR})

macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)

    message("macros ${filename}")
    add_custom_command(
            OUTPUT ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc
            DEPENDS ${_PROTOBUF_PROTOC} ${PROTO_DIR}/${basename}.proto
            COMMAND ${_PROTOBUF_PROTOC} ${PROTO_DIR}/${basename}.proto
            --proto_path=${GENERATED_DIR}
            --cpp_out=${GENERATED_DIR}
            --grpc_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${PROTO_DIR}
            VERBATIM
    )
endmacro(compile_proto_file)

foreach(proto_file ${PROTO_SOURCES})
    message("compiling ${proto_file}")
    compile_proto_file(${proto_file})
    get_filename_component(basename ${proto_file} NAME_WE)
    set(task_manager_generated_files ${task_manager_generated_files} ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc)
endforeach(proto_file)

include_directories(${GENERATED_DIR})
SET_SOURCE_FILES_PROPERTIES(${proto_src} ${proto_hdr} PROPERTIES GENERATED TRUE)
set(generated_files ${proto_src} ${proto_hdr} ${task_manager_generated_files})

include_directories(src)
include_directories(tests)

file(GLOB_RECURSE model_src src/model/* src/utilities/* src/persistence/*)
file(GLOB_RECURSE ui_src src/ui/* src/utilities/* src/model/* src/persistence/*)
file(GLOB_RECURSE model_tests_src tests/model/* tests/utilities/* tests/persistence/*)
file(GLOB_RECURSE ui_tests_src tests/ui/* tests/model/*.h tests/persistence/*.h)

add_executable(TaskManager ${generated_files} ${model_src} ${ui_src} src/main.cpp)
target_link_libraries(TaskManager protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)

add_executable(client ${generated_files} ${ui_src} src/client.cpp)
target_link_libraries(client protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)

add_executable(server ${generated_files} ${model_src} src/server.cpp)
target_link_libraries(server protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)

add_executable(model_tests ${generated_files} ${model_src} ${model_tests_src})
target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(model_tests protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
gtest_discover_tests(model_tests)

add_executable(ui_tests ${generated_files} ${ui_src} ${ui_tests_src})
target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(ui_tests protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
gtest_discover_tests(ui_tests)

add_executable(integration_tests ${generated_files} ${model_src} ${ui_src} tests/IntegrationTest.cpp)
target_link_libraries(integration_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(integration_tests protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
gtest_discover_tests(integration_tests)