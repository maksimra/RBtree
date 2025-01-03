find_package (GTest)

if (NOT GTest_FOUND)
        message (STATUS "GTest not found, downloading GoogleTest...")
        include (FetchContent)
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG release-1.12.1
        )
        set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
endif ()

enable_testing ()

add_executable(
        tree_tests
        ../source/compare.cpp
        tests.cpp
)

target_link_libraries(
        tree_tests
        GTest::gtest_main
)

target_include_directories (tree_tests PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(
        speed_tests
        ../source/compare.cpp
        speed_test.cpp
)

target_link_libraries(
        speed_tests
        GTest::gtest_main
)

target_include_directories (speed_tests PUBLIC ${PROJECT_SOURCE_DIR})

include (GoogleTest)

gtest_discover_tests (tree_tests)
gtest_discover_tests (speed_tests)
