cmake_minimum_required(VERSION 2.69)
project(RadioControl)

set(CMAKE_CXX_STANDARD 11)
set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")

find_package(Boost COMPONENTS system REQUIRED)
include_directories(/usr/local/robotino/api2/include/rec/robotino/api2)

add_executable(RadioControl src/SerialControl/SERIALRead.cpp src/Robot.cpp src/main.cpp)
link_directories(/usr/local/robotino/api2/lib)

target_link_libraries(RadioControl ${Boost_LIBRARIES} -lrec_robotino_api2)
