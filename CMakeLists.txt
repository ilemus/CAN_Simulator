cmake_minimum_required(VERSION 2.6)
project(CANSimulator)
set(sources ${sources}
    src/Message.cpp
    src/configuration.cpp
    src/main.cpp
)
add_executable(CANSimulator ${sources})
