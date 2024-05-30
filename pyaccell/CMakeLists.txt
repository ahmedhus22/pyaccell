set(
    pyaccell_HEADERS
    pyaccell/shader.hpp
    pyaccell/rules.hpp
    pyaccell/engine.hpp
)
set(
    pyaccell_SOURCES
    pyaccell/shader.cpp
    pyaccell/rules.cpp
    pyaccell/engine.cpp
)
nanobind_add_module(pyaccell_ext STABLE_ABI ${pyaccell_HEADERS} ${pyaccell_SOURCES} pyaccell/binding.cpp)
set_target_properties(pyaccell_ext PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pyaccell_ext PRIVATE glfw glad)
target_link_libraries(pyaccell_ext PUBLIC glm)
target_include_directories(pyaccell_ext PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(
    libpyaccell STATIC
    ${pyaccell_HEADERS}
    ${pyaccell_SOURCES}
)
set_target_properties(libpyaccell PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libpyaccell PRIVATE glfw glad)
target_link_libraries(libpyaccell PUBLIC glm)
target_include_directories(libpyaccell PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS pyaccell_ext LIBRARY DESTINATION pyaccell)
