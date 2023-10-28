//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ARBRE_H
#define COURSC_ARBRE_H

#include <iostream>

#include "Obstacle.h"

class Arbre : public Obstacle{
public:
    // Enum
    enum class Etat {planted,growing,mature,fruits,rotten};

    // Attributes
    Etat statutArbre;
    bool isWatered;

    // Constructor
    Arbre(int x, int y, bool isWatered);
    Arbre(int x, int y);

    // Destructor
    ~Arbre();

    // Getters
    bool getIsWatered();
    Etat getStatutArbre();

    // Setters
    void setStatutArbre(Etat statutArbre);
    void setIsWatered(bool isWatered);
    // Methods
    void arroser();
    bool recolter();
    void grandir();
};


#endif //COURSC_ARBRE_H
