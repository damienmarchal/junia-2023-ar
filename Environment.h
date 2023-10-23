//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENVIRONMENT_H
#define COURSC_ENVIRONMENT_H

#include <iostream>
#include <vector>

#include "Entite.h"
/*
#include "Obstacle.h"
#include "Arbre.h"
#include "Robot.h"
 */
class Environment {
    // crée un vecteur 2D de pointeur vers des entités
    std::vector<std::vector<Entite*>> map;
   int size[2];// taile de la map 0:lignes 1:colonnes

public:
    // constructor
    Environment(int x, int y);

    // destructor
    ~Environment();

    // getters
    int* getSize();
    std::vector<std::vector<Entite*>> getMap();

    // setters

    // methods
    void initMap(int pourcentageArbre,int nombreRobot);
    void printMap();

    // TODO : changer les fonctions arooser pour les mettre dans la classe robot
    //void arroser(Robot* robot); // arrose les cases autour du robot

    void genereArbre(int pourcentage);
};


#endif //COURSC_ENVIRONMENT_H
