cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Barcode.cpp Barcode.h QRcode.cpp QRcode.h ImageCorrection.cpp ImageCorrection.h)
find_package(OpenCV REQUIRED)

target_link_libraries(untitled ${OpenCV_LIBS} zbar)
