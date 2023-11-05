//
// Created by cload on 16/10/2023.
//

#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, bool isSolid) : Entite(x, y) {
    this->isSolid = isSolid;
    this->position[0] = x;
    this->position[1] = y;
    this->nom = "X";
}

Obstacle::Obstacle(int x, int y) : Entite(x, y) {
    this->isSolid = true;
    this->position[0] = x;
    this->position[1] = y;
    this->nom = "X";
}
