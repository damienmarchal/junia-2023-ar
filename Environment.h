//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENVIRONMENT_H
#define COURSC_ENVIRONMENT_H

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "Entite.h"

#include "Arbre.h"


class Environment {
    // crée un vecteur 2D de pointeur vers des entités
    std::vector<std::vector<Entite*>> map;
    int size[2];// taile de la map 0:lignes 1:colonnes
    bool running = false;
    float deltaT;
public:
    std::vector<Entite *> allRobots;
    std::vector<Entite *> allArbres;

    // constructor
    Environment(int x, int y);

    // destructor
    ~Environment();

    // getters
    int* getSize();
    float getDeltaT();
    std::vector<std::vector<Entite*>> getMap();
    bool getRunning();

    // setters
    void setRunning(bool running);
    void setMap(std::vector<std::vector<Entite*>> &map);

    // methods
    void initMap(int pourcentageArbre, int nombreRobotArroseur, int nombreRobotPlanteur, int nombreRobotRecolteur);
    void printMap();
    void updateMap();
    void runSimulation();
    void addArbre(int x, int y);

    void genereArbre(int pourcentage);
    void genereRobot(int nombreRobotArroseur, int nombreRobotPlanteur, int nombreRobotRecolteur);
    void genereRobotPlanteur(int nombreRobot);
    void genereRobotArroseur(int nombreRobot);
    void genereRobotRecolteur(int nombreRobot);

    // Static Function
    static std::mt19937::result_type genereteSeed();
    static float CalculDistance(float x1, float y1, float x2, float y2);



};


#endif //COURSC_ENVIRONMENT_H
