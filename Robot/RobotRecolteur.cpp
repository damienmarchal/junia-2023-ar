//
// Created by cload on 23/10/2023.
//

#include "RobotRecolteur.h"

// constructor
RobotRecolteur::RobotRecolteur(int x, int y) : Robot(x, y) {
    this->nom = "R";
    this->position[0] = x;
    this->position[1] = y;
    this->direction = Direction::Nord;
}

// destructor
RobotRecolteur::~RobotRecolteur() = default;

// methods