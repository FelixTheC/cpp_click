cmake_minimum_required(VERSION 3.24)
project(PackageTest CXX)

find_package(cppclick CONFIG REQUIRED)



add_executable(example src/example.cpp)
target_link_libraries(example cppclick::cppclick)
