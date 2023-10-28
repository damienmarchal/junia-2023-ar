//
// Created by cload on 23/10/2023.
//

#include "RobotPlanteur.h"

// constructor
RobotPlanteur::RobotPlanteur(int x, int y) : Robot(x, y) {
    this->nom = "P";
    this->position[0] = x;
    this->position[1] = y;
    this->direction = Robot::Direction::Nord;
}

// methods
void RobotPlanteur::planter(Environment &env) {
    /*
     * Permet de planter un arbre
     */
    // Vérifier que le robot a des graines
    if(this->getCapacity()<0){
        // TODO : si le robot n'a pas de graine, il va chercher des graines
        // TODO : Peut-être mettre en place un système de stratégie par fifo
    }
    else {
        // TODO : vérifier qu'une zone de plantation est disponible
        if (this->isFree()) {
            // Vérifie que toute les cases autour de la zone sont libre
            // récupère les coordonnées de la zone
            int x = this->getPosition()[0];
            int y = this->getPosition()[1];
            Direction direction = this->getDirection();
            // Vérifier que la zone est libre en fonction de la direction pour planter l'arbre
            switch (direction) {
                case Robot::Direction::Nord:
                    if (this->localMap[x][y - 1]->getNom() == "_" && this->localMap[x - 1][y - 1]->getNom() == "_" &&
                        this->localMap[x + 1][y - 1]->getNom() == "_" && this->localMap[x - 1][y]->getNom() == "_" &&
                        this->localMap[x + 1][y]->getNom() == "_") {
                        //planter l'arbre
                        int position[2] = {x, y - 1};
                        //env.addArbre(Arbre(position[0], position[1]), position[0], position[1]);
                        //Retirer une graine au robot
                        this->setCapacity(this->getCapacity() - 1);
                    } else {
                        // TODO : si la zone n'est pas libre, le robot va chercher une autre zone
                        // TODO : Peut-être mettre en place un système de stratégie par fifo
                    }
                    break;
                case Direction::Est:
                    if (this->localMap[x + 1][y]->getNom() == "_" && this->localMap[x + 1][y - 1]->getNom() == "_" &&
                        this->localMap[x + 1][y + 1]->getNom() == "_" && this->localMap[x][y - 1]->getNom() == "_" &&
                        this->localMap[x][y + 1]->getNom() == "_") {
                        //planter l'arbre
                        int position[2] = {x + 1, y};
                        //env.addArbre(Arbre(position[0], position[1]), position[0], position[1]);
                        //Retirer une graine au robot
                        this->setCapacity(this->getCapacity() - 1);
                    }
                    break;
                case Direction::Sud:
                    if (this->localMap[x][y + 1]->getNom() == "_" && this->localMap[x - 1][y + 1]->getNom() == "_" &&
                        this->localMap[x + 1][y + 1]->getNom() == "_" && this->localMap[x - 1][y]->getNom() == "_" &&
                        this->localMap[x + 1][y]->getNom() == "_") {
                        //planter l'arbre
                        int position[2] = {x, y + 1};
                        //env.addArbre(Arbre(position[0], position[1]), position[0], position[1]);
                        //Retirer une graine au robot
                        this->setCapacity(this->getCapacity() - 1);
                    }
                    break;
                case Direction::Ouest:
                    if (this->localMap[x - 1][y]->getNom() == "_" && this->localMap[x - 1][y - 1]->getNom() == "_" &&
                        this->localMap[x - 1][y + 1]->getNom() == "_" && this->localMap[x][y - 1]->getNom() == "_" &&
                        this->localMap[x][y + 1]->getNom() == "_") {
                        //planter l'arbre
                        int position[2] = {x - 1, y};
                        //env.addArbre(Arbre(position[0], position[1]), position[0], position[1]);
                        //Retirer une graine au robot
                        this->setCapacity(this->getCapacity() - 1);
                    }
                    break;

            }
        } else {
            // TODO : si la zone n'est pas libre, le robot va chercher une autre zone
            // TODO : Peut-être mettre en place un système de stratégie par fifo
        }
    }
}

void RobotPlanteur::action(Environment &env) {
    /*
     * Permet de faire l'action du robot
     */

    this->planter(env);

    // TODO : Mettre en place une stratégie de déplacement
}

