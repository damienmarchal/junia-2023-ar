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
#include "Robot/RobotPlanteur.h"
#include "Robot/RobotArroseur.h"
#include "Robot/RobotRecolteur.h"
// constructor
Environment::Environment(int width, int height)  {
    this->size[0] = width;
    this->size[1] = height;
    this->deltaT = 0.1; // On simule l'environement toute les 100 ms
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
float Environment::getDeltaT() { return this->deltaT; }
int *Environment::getSize() { return this->size; }
std::vector<std::vector<Entite *>> Environment::getMap() { return this->map; }
bool Environment::getRunning() { return this->running; }

// setters
void Environment::setRunning(bool running) { this->running = running; }

// methods
void Environment::printMap() {
    /*
     * Permet d'afficher la map
     */
    std::cout << std::endl;
    for (int i = 0; i < this->size[0]; i++) {
        for (int j = 0; j < this->size[1]; j++) {
            std::cout << this->map[i][j]->getNom() <<" | " <<std::flush;
        }
        std::cout << std::endl;

    }
}

std::mt19937::result_type Environment::genereteSeed(){
    /*
     * Permet de générer un seed aléatoire
     * :return: un seed aléatoire
     */

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

    return seed;
}

void Environment::genereArbre(int pourcentage){
    /*
     * Permet de générer des arbres sur la map
     * en fonction de la taille de la map et du pourcentage d'arbre voulu
     * :param pourcentage: pourcentage d'arbre voulu
    */

    // Determine le nombre d'abre à metter en fonction de la taille de la carte
    int nbArbre = (this->size[0] * this->size[1]) * pourcentage/100;

    std::mt19937 gen(genereteSeed());

    std::uniform_int_distribution<unsigned> distrib(1, std::max(this->getSize()[0], this->getSize()[1]) - 1);

    // On place les arbres aléatoirement sur la map
    for (int i = 0; i < nbArbre; i++) {

        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if (this->map[x][y]->getNom() == "_") {// passer cet iteration de boucle
            Arbre *arbre = new Arbre(x, y, false);
            this->allArbres.push_back(arbre); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = arbre; // on ajoute l'arbre à la map
        }
        else {
            i--;
        }
    }

}

void Environment::genereRobot(int nombreRobotArroseur, int nombreRobotPlanteur, int nombreRobotRecolteur){
    /*
     * Permet de générer des robots sur la map
     * :param nombreRobotArroseur: nombre de robot arroseur à générer
     * :param nombreRobotPlanteur: nombre de robot planteur à générer
     * :param nombreRobotRecolteur: nombre de robot récolteur à générer
     */
    // TODO : Trouver un moyen de simplifer les trois boucles for en une seule

    std::mt19937 gen(genereteSeed());
    std::uniform_int_distribution<unsigned> distrib(1, std::max(this->getSize()[0], this->getSize()[1]) - 1);
    for (int i = 0; i < nombreRobotArroseur; i++) {
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotArroseur *robot = new RobotArroseur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
    for(int i=0;i<nombreRobotRecolteur;i++){
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotRecolteur *robot = new RobotRecolteur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
    for(int i=0;i<nombreRobotPlanteur;i++){
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotPlanteur *robot = new RobotPlanteur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
}

void Environment::initMap(int pourcentageArbre, int nombreRobotArroseur, int nombreRobotPlanteur, int nombreRobotRecolteur) {
    /* Permet d'ajouter des obstacles à la map */

    // on ajoute des murs sur les bords
    for (int i = 0; i < this->size[0]; i++) {
        for (int j = 0; j < this->size[1]; j++) {
            if (i == 0 || j == 0 || i == this->size[0] - 1 || j == this->size[1] - 1) {
                this->map[i][j] = new Obstacle(i, j, true);
            }
        }
    }

    // on ajoute des arbres aléatoirement
    genereArbre(pourcentageArbre);

    // on ajoute des robots aléatoirement
    genereRobot(nombreRobotArroseur, nombreRobotPlanteur, nombreRobotRecolteur);

    // on lance la simulation
    this->running = true;

}

void Environment::updateMap() {
    /*
     * Permet de mettre à jour la map
     * Et de faire en sorte que toutes les entités évoluent dans l'environnement
     */

    // Avant chaque update on prends 1000 ms de pause
    sleep(1); // TODO : Doit être supprimer pour la version finale

    // Permet au arbre de grandir
    for(auto item:this->allArbres){
        // cast pour avoir sa class
        Arbre* arbre = dynamic_cast<Arbre *>(item); // Permet de travailler avec le classe arbre
        arbre->grandir();
    }

    // Demande à chaque robot l'action qu'il veut faire
    for(auto item:this->allRobots){
        // on regarde comment cast le robot
        // TODO : faire une template pour éviter la répétition de code
        if(item->getNom()=="R"){
            // cast pour avoir sa class
            RobotRecolteur* robot = dynamic_cast<RobotRecolteur *>(item); // Permet de travailler avec le classe arbre
            robot->Update(*this); // Permet d'actualiser les données du robot
            robot->priseDecision(*this); // Permet de prendre une décision en fonction de sa stratégie et de l'environement
            robot->action(*this); // Permet d'agir en fonction de sa décision
        }
        else if(item->getNom()=="W"){
            // cast pour avoir sa class
            RobotArroseur* robot = dynamic_cast<RobotArroseur *>(item); // Permet de travailler avec le classe arbre
            robot->Update(*this); // Permet d'actualiser les données du robot
            robot->priseDecision(*this); // Permet de prendre une décision en fonction de sa stratégie et de l'environement
            robot->action(*this); // Permet d'agir en fonction de sa décision
        }
        else if(item->getNom()=="P"){
            RobotPlanteur* robot = dynamic_cast<RobotPlanteur *>(item); // Permet de travailler avec le classe arbre
            robot->Update(*this); // Permet d'actualiser les données du robot
            robot->priseDecision(*this); // Permet de prendre une décision en fonction de sa stratégie et de l'environement
            robot->action(*this); // Permet d'agir en fonction de sa décision
        }

    }
}

void Environment::runSimulation() {
    /*
     * Permet de lancer la simulation
     */
    while (this->getRunning()) {
        // on met à jour la map
        this->updateMap();
        // on affiche la map
        this->printMap();
    }
}


// TODO : Implémeter une template pour éviter la répétition de code
void Environment::genereRobotArroseur(int nombreRobot) {
    /*
     * Permet de générer des robots arroseurs sur la map
     */
    std::mt19937 gen(genereteSeed()); // génération de random
    std::uniform_int_distribution<unsigned> distrib(1, std::max(this->getSize()[0], this->getSize()[1]) - 1); // distribution aléatoire

    // on ajoute les robots arroseurs
    for(int i=0;i<nombreRobot;i++){
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotArroseur *robot = new RobotArroseur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
}

void Environment::genereRobotPlanteur(int nombreRobot) {
    /*
     * Permet de générer des robots planteurs sur la map
     * :param nombreRobot: nombre de robot à générer
     */
    std::mt19937 gen(genereteSeed()); // génération de random
    std::uniform_int_distribution<unsigned> distrib(1, std::max(this->getSize()[0], this->getSize()[1]) - 1); // distribution aléatoire

    // on ajoute les robots planteurs
    for(int i=0;i<nombreRobot;i++){
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotPlanteur *robot = new RobotPlanteur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
}

void Environment::genereRobotRecolteur(int nombreRobot) {
    /*
     * Permet de générer des robots récolteurs sur la map
     * :param nombreRobot: nombre de robot à générer
     */
    std::mt19937 gen(genereteSeed()); // génération de random
    std::uniform_int_distribution<unsigned> distrib(1, std::max(this->getSize()[0], this->getSize()[1]) - 1); // distribution aléatoire

    // on ajoute les robots récolteurs
    for(int i=0;i<nombreRobot;i++){
        int x = distrib(gen);
        int y = distrib(gen);
        // vérifie si la case est vide
        if(this->map[x][y]->getNom() == "_"){
            RobotRecolteur *robot = new RobotRecolteur(x, y);
            this->allRobots.push_back(robot); // on ajoute l'arbre à la liste des arbres
            this->map[x][y] = robot; // on ajoute l'arbre à la map
        }// passer cet iteration de boucle
        else{
            i--;
        }
    }
}

void Environment::setMap(std::vector<std::vector<Entite *>> &map) {
    /*
     * Permet de mettre à jour la map
     * :param map: nouvelle map
     */
    this->map = map;

}

