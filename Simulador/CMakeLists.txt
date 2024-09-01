cmake_minimum_required(VERSION 3.29)
project(mo_601_projeto_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Simulador main.cpp
        Memory.cpp
        Memory.h
        Instruction.cpp
        Instruction.h
        Executor.cpp
        Executor.h
        CPU.cpp
        CPU.h
        instruction_codes.h
)
