project(tests)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

file(GLOB_RECURSE model_tests_src CONFIGURE_DEPENDS
        "../src/model/*.h"
        "../src/model/*.cpp"
        "model/*.h"
        "model/*.cpp"
        )

add_executable(model_tests ${model_tests_src})

target_link_libraries(model_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(model_tests)

file(GLOB_RECURSE ui_tests_src CONFIGURE_DEPENDS
        "../src/*.h"
        "../src/*.cpp"
        "ui/*.h"
        "ui/*.cpp"
        )

add_executable(ui_tests ${ui_tests_src})

target_link_libraries(ui_tests GTest::gtest GTest::gmock GTest::gmock_main)

gtest_discover_tests(ui_tests)
