cmake_minimum_required(VERSION 3.10)

project(image_process)
set(CMAKE_BUILD_TYPE Release)

# OpenCV
set(OpenCV_DIR "E:/package/opencv-3.4.20/mingw_build/install")
# set(OpenCV_DIR "E:/package/opencv-3.4.20/mingw_build_without_qt/win-install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV_VERSION = ${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")

# exe
add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS})

add_executable(histogram examples/histogram.cpp)
target_link_libraries(histogram ${OpenCV_LIBS})
# cmake -G "MinGW Makefiles" ..
