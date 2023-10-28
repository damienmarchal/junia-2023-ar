//
// Created by cload on 23/10/2023.
//

#include "RobotArroseur.h"

// constructor
RobotArroseur::RobotArroseur(int x, int y) : Robot(x, y) {
    this->position[0] = x;
    this->position[1] = y;
    this->nom = "A";
}

void RobotArroseur::arroser() {
    if(this->position[0] == 0 && this->position[1] == 0)
        std::cout << "Arrosage en cours" << std::endl;
}

void RobotArroseur::priseDecision(Environment &env) {
    /*
     * Permet de metter en place la stratégie d'arrosage
     * la stratégie est la suivante : si il y a un arbre à arroser, on l'arrose
     * sinon on se déplace jusqu'à trouver un arbre à arroser
     */

    // Vérifie s'il y a déjà une pose disérer à atteindre
    if(this->getActualManeuver() == Robot::ActualManeuver::Mouvement) { // une direction est déjà définie
        return;
    }
    else if(this->getActualManeuver() == Robot::ActualManeuver::Idle){ // aucune direction n'est définie
        // Scanner l'environnement pour vérifier s'il y a un arbre à arroser
        for(int x=0;x<getLocalMap().size()-1;x++){
            for(int y=0;y<getLocalMap()[x].size()-1;y++){
                if(getLocalMap()[x][y]->getNom() == "A"){ // Si c'est un arbre
                    Arbre *arbre = (Arbre *) getLocalMap()[x][y];
                    if(!arbre->getIsWatered()){ // Si l'arbre n'est pas encore arrosé
                        this->setDesiredPose((float)x,(float)y,0);
                        this->setActualManeuver(Robot::ActualManeuver::Mouvement);
                        return;
                    }
                }
            }
        }
    }
}

