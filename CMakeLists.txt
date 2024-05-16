cmake_minimum_required(VERSION 3.29)
project(pyaccell VERSION 1.0.0)

include(CTest)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/googletest)

add_subdirectory(pyaccell)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/pyaccell/pyaccell/")

enable_testing()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
#add_subdirectory(examples/example1)
