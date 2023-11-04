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
        if (this->isFreeZoneToPlant()) {
            // TODO : planter un arbre
        }
        else {
            // TODO : si la zone de plantation n'est pas disponible, le robot va chercher une zone de plantation
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

bool RobotPlanteur::isFreeZoneToPlant() {
    /*
     * Permet de vérifier si la zone de plantation est libre
     */
    // TODO : Vérifier que la zone de plantation est libre
    return true;
}

