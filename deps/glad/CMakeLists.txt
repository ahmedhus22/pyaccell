cmake_minimum_required(VERSION 3.15...3.29)
project(glad VERSION 4.1)

add_library(glad)
target_sources(glad PRIVATE src/glad.c)
target_include_directories(glad PUBLIC include)