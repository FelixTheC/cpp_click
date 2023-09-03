cmake_minimum_required(VERSION 3.24)
project(cppclick VERSION 1.0 LANGUAGES CXX)

if ("$ENV{TESTING}")
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )

    FetchContent_MakeAvailable(googletest)
    include_directories(${antlr4-runtime_INCLUDE_DIR}
            ${antlr4-cppruntime_LIB_DIRS_RELEASE}
            ${GTEST_INCLUDE_DIRS}
            cpp_parsing)

    add_executable(${PROJECT_NAME}
            src/click.cpp
            include/click.hpp
            include/clickOption.hpp
            include/clickArgument.hpp
            tests/testmain.cpp
            tests/test_click.cpp
            tests/test_click_option.cpp
            tests/test_click_argument.cpp
            include/utils.hpp)

    target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME})
else ()
    add_library(${PROJECT_NAME} src/click.cpp src/clickOption.cpp src/clickArgument.cpp)
    target_include_directories(${PROJECT_NAME} PUBLIC include)
endif ()

if ("$ENV{GCC}")
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
            -fsanitize=address
    )
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
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