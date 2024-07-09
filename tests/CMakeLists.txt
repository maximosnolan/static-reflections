cmake_minimum_required(VERSION 3.10)
project(ReflectionTests)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(
    refl
)

add_executable(reflectTest reflect_class.t.m.cc)

# Link the 'servicelib' library to 'fileExplorer'
target_link_libraries(reflectTest PRIVATE refl)

