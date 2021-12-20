project(tests)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()


file(GLOB_RECURSE model_tests_src CONFIGURE_DEPENDS
        "../src/model/*.h"
        "../src/model/*.cpp"
        "model/*.cpp"
        )
add_executable(model_tests ${model_tests_src})

target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)
gtest_discover_tests(model_tests)


file(GLOB_RECURSE persistence_tests_src CONFIGURE_DEPENDS
        "../src/persistence/*.h"
        "../src/persistence/*cpp"
        "../src/model/Comparison.h"
        "../src/model/Comparison.cpp"
        "persistence/*.cpp"
        )

add_executable(persistence_tests ${proto_src} ${proto_hdr} ${persistence_tests_src})

target_link_libraries(persistence_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(persistence_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(persistence_tests)


file(GLOB_RECURSE ui_tests_src CONFIGURE_DEPENDS
        "../src/model/*.h"
        "../src/model/*.cpp"
        "../src/ui/*.h"
        "../src/ui/*cpp"
        "ui/*.cpp"
        "ui/*.h"
        )

add_executable(ui_tests ${proto_src} ${proto_hdr} ${ui_tests_src})

target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(ui_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(ui_tests)


file(GLOB_RECURSE integration_tests_src CONFIGURE_DEPENDS
        "../src/model/*.h"
        "../src/model/*.cpp"
        "../src/ui/*.h"
        "../src/ui/*cpp"
        "../src/persistence/*.h"
        "../src/persistence/*.cpp"
        )

add_executable(integration_tests ${proto_src} ${proto_hdr} ${integration_tests_src} MainTest.cpp)

target_link_libraries(integration_tests GTest::gtest GTest::gmock GTest::gmock_main)
target_link_libraries(integration_tests ${Protobuf_LIBRARIES})
gtest_discover_tests(integration_tests)


include_directories(ui/context)
include_directories(ui/controller)
include_directories(ui/dependency)
include_directories(ui/factory)
include_directories(ui/machine)
include_directories(ui/step)
include_directories(ui/view)