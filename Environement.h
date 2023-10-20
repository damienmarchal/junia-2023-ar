//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENVIRONEMENT_H
#define COURSC_ENVIRONEMENT_H

#include <iostream>
#include <vector>

#include "Entite.h"
#include "Robot.h"
/*
#include "Obstacle.h"
#include "Arbre.h"
#include "Robot.h"
 */
class Environement {
    // crée un vecteur 2D de pointeur vers des entités
    std::vector<std::vector<Entite*>> map;
   int size[2];// taile de la map 0:lignes 1:colonnes

public:
    Environement(int x, int y);
    void initMap(int pourcentageArbre,int nombreRobot);
    void printMap();
    int* getSize();
    void arroser(Robot* robot);
/*
    void addRobot(Robot robot);
    void addArbre(Arbre arbre, int x, int y);
*/


    void genereArbre(int pourcentage);
};


#endif //COURSC_ENVIRONEMENT_H
