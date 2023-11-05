//
// Created by cload on 16/10/2023.
//

#include "Entite.h"

Entite::Entite(int x, int y) {
    position[0] = x;
    position[1] = y;
    this->nom = "_";
}

void Entite::set_Position(int x, int y) {
    position[0] = x;
    position[1] = y;
}

std::string Entite::getNom() {
    return this->nom;

}

int *Entite::getPosition() {
    return this->position;
}
