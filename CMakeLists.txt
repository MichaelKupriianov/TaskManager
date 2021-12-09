cmake_minimum_required(VERSION 3.20)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/model/)
include_directories(src/model/id)
include_directories(src/ui/)
include_directories(src/ui/context/)
include_directories(src/ui/controller/)
include_directories(src/ui/dependency/)
include_directories(src/ui/factory/)
include_directories(src/ui/machine/)
include_directories(src/ui/step/)
include_directories(src/ui/view/)

file(GLOB_RECURSE TaskManager_src CONFIGURE_DEPENDS
        "src/*.h"
        "src/*.cpp"
        )

add_executable(TaskManager ${TaskManager_src})

add_subdirectory(tests)