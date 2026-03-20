cmake_minimum_required(VERSION 4.1)
project(Calc)

set(CMAKE_CXX_STANDARD 20)

add_executable(Calc src/main.cpp
        include/Equation.h
        include/Token.h
        src/Lexer.cpp
        include/Lexer.h
        src/Parser.cpp
        include/Parser.h
        src/Evaluator.cpp
        include/Evaluator.h
        Custom_Errors.h)
