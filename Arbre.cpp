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

// Destructor
Arbre::~Arbre() = default;

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

    // Une fois que l'arbre à donner des fruits, il n'est plus arrosé
    if(this->getStatutArbre() == Etat::fruits || this->getStatutArbre() == Etat::mature){
        this->setIsWatered(false);
    }
}

bool Arbre::recolter() {
    /*
     * Permet de récolter les fruits de l'arbre
     */
    if(this->getStatutArbre() == Etat::fruits){ // Si l'arbre est à l'état fruit
        this->setStatutArbre(Etat::growing); // On le remet à l'état de pousse
        this->setIsWatered(false); // On le remet à l'état non arrosé
        return true; // On retourne true pour dire que l'arbre a été récolté
    }
    return false;
}



