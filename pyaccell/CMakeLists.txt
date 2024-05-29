add_library(
    pyaccell SHARED
    pyaccell/shader.hpp
    pyaccell/rules.hpp
    pyaccell/engine.hpp
    pyaccell/shader.cpp
    pyaccell/rules.cpp
    pyaccell/engine.cpp
)

set_target_properties(pyaccell PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pyaccell PRIVATE glfw glad)
target_link_libraries(pyaccell PUBLIC glm)
target_include_directories(pyaccell PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

nanobind_add_module(binding pyaccell/binding.cpp)
# target_link_libraries(binding PRIVATE .....)