cmake_minimum_required(VERSION 3.24)
project(cppclick VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} src/click.cpp src/clickOption.cpp src/clickArgument.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Werror
            -Wpedantic
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wfloat-conversion
            -fno-omit-frame-pointer
    )
    target_link_options(${PROJECT_NAME} PRIVATE)
endif ()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES
                        PUBLIC_HEADER "include/clickOption.hpp;include/clickArgument.hpp;include/click.hpp"
                        VERSION ${PROJECT_VERSION}
                        CXX_STANDARD 20
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS NO
                        )

install(TARGETS ${PROJECT_NAME})