cmake_minimum_required(VERSION 4.1)
project(Calc)

set(CMAKE_CXX_STANDARD 20)


# -----------------------------
# Try to find VecMatLib first
# -----------------------------
find_package(VecMatLib QUIET)

# -----------------------------
# If not found, fetch from GitHub
# -----------------------------
if(NOT VecMatLib_FOUND)
    include(FetchContent)

    message(STATUS "VecMatLib not found. Fetching from GitHub...")

    FetchContent_Declare(
            VecMatLib
            GIT_REPOSITORY https://github.com/chickenBicen/VecMatLib.git
            GIT_TAG main  # or a specific release tag/commit
    )

    FetchContent_MakeAvailable(VecMatLib)
endif()



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

target_link_libraries(Calc PRIVATE VecMatLib)