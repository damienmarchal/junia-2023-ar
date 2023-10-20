//
// Created by cload on 16/10/2023.
//

#include "Arbre.h"

Arbre::Arbre(int x, int y, bool isWatered) : Obstacle(x, y, isSolid) {
    this->position[0] = x;
    this->position[1] = y;
    this->isWatered = isWatered;
    Obstacle::isSolid = true;
    this->nom = "A";
}

bool Arbre::getIsWatered() {
    return isWatered;
}

void Arbre::arroser() {
    isWatered = true;
}
