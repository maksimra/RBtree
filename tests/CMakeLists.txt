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

#----RBtreeKeyTest-------------------------------

add_executable(
        RBtreeKeyTest
        RBtreeKeyTest.cpp
        ../source/compare.cpp
)

target_link_libraries(
        RBtreeKeyTest
        GTest::gtest_main
)

target_include_directories (RBtreeKeyTest PUBLIC ${PROJECT_SOURCE_DIR}
                                                 ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests (RBtreeKeyTest)

#----StdSetKeyTest-------------------------------

add_executable(
        StdSetKeyTest
        StdSetKeyTest.cpp
)

target_link_libraries(
        StdSetKeyTest
        GTest::gtest_main
)

target_include_directories (StdSetKeyTest PUBLIC ${PROJECT_SOURCE_DIR}
                                                 ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests (StdSetKeyTest)

#----RBtreeBenchmark-----------------------------

add_executable(
        RBtreeBenchmark
        RBtreeBenchmark.cpp
        ../source/compare.cpp
)

target_link_libraries(
        RBtreeBenchmark
        GTest::gtest_main
)

target_include_directories (RBtreeBenchmark PUBLIC ${PROJECT_SOURCE_DIR}
                                                   ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests (RBtreeBenchmark)

#----StdSetBenchmark-----------------------------

add_executable(
        StdSetBenchmark
        StdSetBenchmark.cpp
)

target_link_libraries(
        StdSetBenchmark
        GTest::gtest_main
)

target_include_directories (StdSetBenchmark PUBLIC ${PROJECT_SOURCE_DIR}
                                                   ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests (StdSetBenchmark)

#------------------------------------------------

include (GoogleTest)

