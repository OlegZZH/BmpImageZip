cmake_minimum_required(VERSION 3.14)
project(CompressorLib)

set(CMAKE_CXX_STANDARD 17)

add_library(compressor STATIC
        compressor.h
)

target_include_directories(compressor PUBLIC .)