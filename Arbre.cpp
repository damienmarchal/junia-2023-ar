//
// Created by cload on 16/10/2023.
//

#include "Arbre.h"

// Constructor
Arbre::Arbre(int x, int y) : Obstacle(x, y) {
    this->position[0] = x;
    this->position[1] = y;

    Obstacle::isSolid = true;
    this->nom = "A";

    this->statutArbre = Etat::planted;
}

Arbre::Arbre(int x, int y, bool isWatered) : Obstacle(x, y) {
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

Arbre::Etat Arbre::getStatutArbre() {
    return this->statutArbre;
}

Arbre::Etat Arbre::setStatutArbre(Arbre::Etat statutArbre) {
    return this->statutArbre = statutArbre;
}

void Arbre::grandir() {
    if (this->statutArbre == Etat::rotten) { return; } // si les fruits sont pourrit on reste dans cette etat
    if(this->isWatered){
        this->statutArbre =  (Etat) ((int) this->statutArbre + 1); // on passe a l'etat suivant dans tous les autres cas
    }
}

Arbre::~Arbre() = default;
