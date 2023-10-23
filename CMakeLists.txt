cmake_minimum_required(VERSION 3.26)
project(CoursC)

set(CMAKE_CXX_STANDARD 17)

add_executable(CoursC main.cpp
        Environement.cpp
        Environement.h
        Robot/Robot.cpp
        Robot/Robot.h
        Obstacle.cpp
        Obstacle.h
        Arbre.cpp
        Arbre.h
        Entite.cpp
        Entite.h)
