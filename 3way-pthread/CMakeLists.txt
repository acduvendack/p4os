cmake_minimum_required (VERSION 2.8)
project(3way-pthread)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -D_XOPEN_SOURCE=500")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -Wno-sign-compare -D_XOPEN_SOURCE=500")

# make an executable
add_executable(${PROJECT_NAME}_slurm src/main.c)
target_compile_definitions(${PROJECT_NAME}_slurm PRIVATE)
target_link_libraries(${PROJECT_NAME}_slurm pthread)