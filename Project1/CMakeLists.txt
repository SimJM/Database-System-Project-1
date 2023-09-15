cmake_minimum_required(VERSION 3.26)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 src/main.cpp
        src/Storage/Storage.h
        src/Storage/Storage.cpp
        src/Indexing/BPlusTree.cpp
        src/Indexing/BPlusTree.h
        src/Storage/Record.cpp
        src/Storage/Record.h
        src/Storage/Block.h
        src/Storage/Block.cpp
        src/Storage/Parser.cpp
        src/Storage/Parser.h)
