cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
find_program(_PROTOBUF_PROTOC protoc)

include_directories(src/model/)
include_directories(src/ui/)
include_directories(src/ui/context/)
include_directories(src/ui/controller/)
include_directories(src/ui/dependency/)
include_directories(src/ui/factory/)
include_directories(src/ui/machine/)
include_directories(src/ui/step/)
include_directories(src/ui/view/)
include_directories(src/persistence/)

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS src/persistent/*.proto)
message("PROTO_SOURCES ${PROTO_SOURCES}")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(proto_src proto_hdr src/model/Task.proto)
message("${proto_hdr}")

file(GLOB_RECURSE TaskManager_src CONFIGURE_DEPENDS
        "src/*.h"
        "src/*.cpp"
        )

add_executable(TaskManager ${proto_src} ${proto_hdr} ${TaskManager_src})

target_link_libraries(TaskManager ${Protobuf_LIBRARIES})

add_subdirectory(tests)