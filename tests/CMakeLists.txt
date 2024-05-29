add_executable(sim_tests sim_tests.cpp)
target_link_libraries(sim_tests PRIVATE GTest::gtest_main libpyaccell)

include(GoogleTest)
gtest_discover_tests(sim_tests)
