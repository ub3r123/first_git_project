cmake_minimum_required(VERSION 3.24)
project(generation_of_labirint C)

set(CMAKE_C_STANDARD 11)

add_executable(generation_of_labirint main.c labirint_1.c labirint_2.c labirint_3.c "labirint_4(hard).c")
