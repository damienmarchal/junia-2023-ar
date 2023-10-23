//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENVIRONEMENT_H
#define COURSC_ENVIRONEMENT_H

#include <iostream>
#include <vector>

#include "Entite.h"
#include "Robot/Robot.h"
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
    // constructor
    Environement(int x, int y);

    // destructor
    ~Environement();

    // getters
    int* getSize();
    std::vector<std::vector<Entite*>> getMap();

    // setters

    // methods
    void initMap(int pourcentageArbre,int nombreRobot);
    void printMap();

    // TODO : changer les fonctions arooser pour les mettre dans la classe robot
    void arroser(Robot* robot); // arrose les cases autour du robot
/*
    void addRobot(Robot robot);
    void addArbre(Arbre arbre, int x, int y);
*/

    void genereArbre(int pourcentage);
};


#endif //COURSC_ENVIRONEMENT_H
