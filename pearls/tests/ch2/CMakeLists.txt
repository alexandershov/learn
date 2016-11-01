include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_pearl_tests_ch2
        test_shift.cpp)

target_link_libraries(run_pearl_tests_ch2 gtest gtest_main)
target_link_libraries(run_pearl_tests_ch2 pearls_lib)
