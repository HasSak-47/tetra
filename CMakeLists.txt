cmake_minimum_required(VERSION 3.11)
project(Game)

set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_THREAD_LIBS_INIT "-lpthread")
#set(CMAKE_HAVE_THREADS_LIBRARY 1)
#set(CMAKE_USE_WIN32_THREADS_INIT 0)
#set(CMAKE_USE_PTHREADS_INIT 1)
#set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} "include")

file(GLOB COMPILATION_UNITS "src/*.cpp")
add_executable(tetris ${COMPILATION_UNITS})

# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(tetris ${SDL2_LIBRARIES})
