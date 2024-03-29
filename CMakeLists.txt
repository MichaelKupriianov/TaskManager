cmake_minimum_required(VERSION 3.20)
project(TaskManager)
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
find_package(GTest CONFIG REQUIRED)
enable_testing()

set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=nullability")

find_package(Boost REQUIRED log_setup log program_options COMPONENTS)
if (Boost_FOUND)
    message(STATUS "Using BOOST ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

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
            --grpc_out=generate_mock_code=true:${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${PROTO_DIR}
            VERBATIM
    )
endmacro(compile_proto_file)

foreach (proto_file ${PROTO_SOURCES})
    message("compiling ${proto_file}")
    compile_proto_file(${proto_file})
    get_filename_component(basename ${proto_file} NAME_WE)
    set(task_manager_generated_files ${task_manager_generated_files} ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc)
endforeach (proto_file)

include_directories(${GENERATED_DIR})
SET_SOURCE_FILES_PROPERTIES(${proto_src} ${proto_hdr} PROPERTIES GENERATED TRUE)
set(generated_files ${proto_src} ${proto_hdr} ${task_manager_generated_files})

include_directories(src)
include_directories(tests)

file(GLOB_RECURSE server_src src/model/* src/persistence/* src/utilities/* src/logging/*)
file(GLOB_RECURSE client_src src/ui/* src/utilities/* src/logging/*)
file(GLOB_RECURSE tests_src tests/*)

add_executable(TaskManager ${generated_files} ${server_src} ${client_src} src/main.cpp)
target_link_libraries(TaskManager protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection ${Boost_LIBRARIES})

add_executable(client ${generated_files} ${client_src} src/client.cpp)
target_link_libraries(client protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection ${Boost_LIBRARIES})

add_executable(server ${generated_files} ${server_src} src/server.cpp)
target_link_libraries(server protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection ${Boost_LIBRARIES})

add_executable(tests ${generated_files} ${server_src} ${client_src} ${tests_src})
target_link_libraries(tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(tests protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection ${Boost_LIBRARIES})
gtest_discover_tests(tests)