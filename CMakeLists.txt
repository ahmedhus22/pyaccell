cmake_minimum_required(VERSION 3.15...3.29)
project(pyaccell VERSION 1.0.0)

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.8 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED
    OPTIONAL_COMPONENTS Development.SABIModule
)
#find_package(nanobind CONFIG REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(CTest)
add_subdirectory(deps/nanobind)
add_subdirectory(deps/glad)
add_subdirectory(deps/glm)
add_subdirectory(deps/glfw)
add_subdirectory(deps/googletest)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(${CMAKE_PROJECT_NAME})

target_compile_definitions(lib${CMAKE_PROJECT_NAME} PUBLIC SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/pyaccell/pyaccell/")
target_compile_definitions(${CMAKE_PROJECT_NAME}_ext PUBLIC SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/pyaccell/pyaccell/")

enable_testing()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
#add_subdirectory(examples/example1)
