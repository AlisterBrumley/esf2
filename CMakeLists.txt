#
cmake_minimum_required(VERSION 3.20)
project(esf2)
include_directories(src)
add_executable(esf2 
    src/esf2.c
    src/filenameset.c
    src/filewrite.c
    src/iterators.c
    src/structfill.c
    src/verify.c)