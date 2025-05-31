cmake_minimum_required(VERSION 3.28)
project(CourseWork)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseWork main.cpp
        json.hpp
        ComponentBase/ComponentBase.h
        ComponentBase/ComponentBase.cpp
        Database/Database.h
        Database/Database.cpp
        University/University.h
        University/University.cpp
        Institute/Institute.h
        Institute/Institute.cpp
        Department/Department.h
        Department/Department.cpp)
