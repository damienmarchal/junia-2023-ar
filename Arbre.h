//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ARBRE_H
#define COURSC_ARBRE_H

#include "Obstacle.h"
class Arbre : public Obstacle{
public:
    Arbre(int x, int y, bool isWatered);
    bool isWatered;
    void water();
    bool getIsWatered();

    void arroser();
};


#endif //COURSC_ARBRE_H
