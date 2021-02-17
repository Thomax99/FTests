cmake_minimum_required(VERSION 3.3)
project (FTests)
set(CMAKE_C_FLAGS "-std=c99 -Wall") ### options communes
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG --coverage") ### options spécifiques
set(CMAKE_C_FLAGS_RELEASE "-O3") ### options spécifiques

include_directories(../include)


add_executable(ftests main.c tests.c ftests_get_args.c utilitaries.c func_args.c)
add_executable(file_test test_file.c)

target_link_libraries(ftests m)