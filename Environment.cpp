//
// Created by cload on 16/10/2023.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <unistd.h> // Permet de faire le sleep

#include "Environment.h"
#include "Arbre.h"
#include "Robot/Robot.h"

// constructor
Environment::Environment(int width, int height)  {
    this->size[0] = width;
    this->size[1] = height;

    // mise en place de la map
    for (int i = 0; i < width; i++) {
        std::vector<Entite *> ligne;
        for (int j = 0; j < height; j++) {
            ligne.push_back(new Entite(i, j));
        }
        this->map.push_back(ligne);
    }
}

// destructor
Environment::~Environment() = default;

// getters
int *Environment::getSize() {
    return this->size;
}
std::vector<std::vector<Entite *>> Environment::getMap() {
    return this->map;
}
bool Environment::getRunning() { return this->running; }

// setters
void Environment::setRunning(bool running) { this->running = running; }

// methods
void Environment::printMap() {
    std::cout << std::endl;
    for (int i = 0; i < this->size[0]; i++) {
        for (int j = 0; j < this->size[1]; j++) {
            std::cout << this->map[i][j]->getNom() <<" | " <<std::flush;
        }
        std::cout << std::endl;

    }
}

void Environment::genereArbre(int pourcentage){
    /*
     * Permet de générer des arbres sur la map
     * en fonction de la taille de la map et du pourcentage d'arbre voulu
     * :param pourcentage: pourcentage d'arbre voulu
    */

    // Determine le nombre d'abre à metter en fonction de la taille de la carte
    int nbArbre = (this->size[0] * this->size[1]) / pourcentage;

    // génération de random
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    Environment env(5, 5);

    std::uniform_int_distribution<unsigned> distrib(1, std::max(env.getSize()[0], env.getSize()[1]) - 1);

    // On place les arbres aléatoirement sur la map
    for (int i = 0; i < nbArbre; i++) {

        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if (this->map[x][y]->getNom() == "_") {// passer cet iteration de boucle
            this->map[x][y] = new Arbre(x, y, false); // on ajoute l'arbre à la map
        }
        else {
            i--;
        }
    }

}

void Environment::genereRobot(int nombreRobot){
    // génération de random
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    Environment env(5, 5);

    std::uniform_int_distribution<unsigned> distrib(1, std::max(env.getSize()[0], env.getSize()[1]) - 1);
    for (int i = 0; i < nombreRobot; i++) {
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            this->map[x][y] = new Robot(x, y); // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
}

void Environment::initMap(int pourcentageArbre, int nombreRobot) {
    /* Permet d'ajouter des obstacles à la map */

    // on ajoute des murs sur les bords
    for (int i = 0; i < this->size[0]; i++) {
        for (int j = 0; j < this->size[1]; j++) {
            if (i == 0 || j == 0 || i == this->size[0] - 1 || j == this->size[1] - 1) {
                this->map[i][j] = new Obstacle(i, j, true);
            }
        }
    }

    // TODO : il y a un problème avec le random la dernière ligne et la dernière colone en 7x7 ne sont jamais rempli
    // on ajoute des arbres aléatoirement
    genereArbre(pourcentageArbre);

    // on ajoute des robots aléatoirement
    genereRobot(nombreRobot);

    // on lance la simulation
    this->running = true;

}

void Environment::updateMap() {
    /*
     * Permet de mettre à jour la map
     */

    // Avant chaque update on prends 1000 ms de pause
    sleep(1);

    // Permet au arbre de grandir
    for(auto item:this->allArbres){
        // cast pour avoir sa class
        Arbre* arbre = dynamic_cast<Arbre *>(item); // Permet de travailler avec le classe arbre
        arbre->grandir();
    }

    // Demande à chaque robot l'action qu'il veut faire
    for(auto item:this->allRobots){
        // cast pour avoir sa class
        Robot* robot = dynamic_cast<Robot *>(item); // Permet de travailler avec le classe arbre
        robot->action(*this);
    }

}



/*
void Environment::arroser(Robot *robot) {
    // on récupère la position du robot
    int x = robot->getPosition()[0];
    int y = robot->getPosition()[1];

    // on vérifie si la case est un arbre
    if (this->map[x][y]->getNom() == "A") {
        // on cast la case en arbre
        Arbre *arbre = dynamic_cast<Arbre *>(this->map[x][y]);
        // on arrose l'arbre
        if(!arbre->getIsWatered()){
            arbre->arroser();
        }
    }
}
*/



/*
void Environment::addArbre(Arbre arbre, int x, int y) {
    // on ajoute l'arbre à la map
    this->map[x][y] = &arbre;
}
*/