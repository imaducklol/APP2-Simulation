cmake_minimum_required(VERSION 3.22)
project(APP2-Simulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(APP2-Simulation main.cpp)



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp)
#add_executable(HelloSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(APP2-Simulation sfml-system sfml-window sfml-graphics sfml-audio sfml-network)