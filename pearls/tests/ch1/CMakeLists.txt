include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_pearl_tests
        test_ex3.cpp test_ex4.cpp test_endianness.cpp test_ex2.cpp test_ex1.cpp test_ex6.cpp)

target_link_libraries(run_pearl_tests gtest gtest_main)
target_link_libraries(run_pearl_tests pearls_lib)
