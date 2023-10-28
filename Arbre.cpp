//
// Created by cload on 16/10/2023.
//

#include "Arbre.h"

// Constructor
Arbre::Arbre(int x, int y) : Obstacle(x, y) {
    this->position[0] = x;
    this->position[1] = y;
    this->isWatered = true;
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
    this->statutArbre = Etat::planted;
}

// Getters
bool Arbre::getIsWatered() { return isWatered; }

// Setters
Arbre::Etat Arbre::getStatutArbre() { return this->statutArbre; }
void Arbre::setIsWatered(bool isWatered) { this->isWatered = isWatered;}
void Arbre::setStatutArbre(Arbre::Etat statutArbre) { this->statutArbre = statutArbre; }

// Methods
void Arbre::arroser() { this->setIsWatered(true); }






void Arbre::grandir() {
    if (this->getStatutArbre() == Etat::rotten) { return; } // si les fruits sont pourrit on reste dans cette etat

    // on passe a l'etat suivant dans tous les autres cas
    if(this->getIsWatered()){ this->setStatutArbre((Etat) ((int) this->getStatutArbre() + 1));}

    // Une fois que l'arbre s'est développé on le deshydrate
    this->setIsWatered(false);
}



Arbre::~Arbre() = default;
