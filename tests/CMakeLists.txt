add_executable(shader_tests shader_tests.cpp)
target_link_libraries(shader_tests PRIVATE GTest::gtest_main pyaccell)

include(GoogleTest)
gtest_discover_tests(shader_tests)
