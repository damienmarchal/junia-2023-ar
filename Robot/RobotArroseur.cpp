//
// Created by cload on 23/10/2023.
//

#include "RobotArroseur.h"

// constructor
RobotArroseur::RobotArroseur(int x, int y) : Robot(x, y) {
    this->position[0] = x;
    this->position[1] = y;
    this->nom = "W"; // W pour Water car A est déjà pris par Arbre
    this->capacity = 10;
}

void RobotArroseur::arroser() {
    /*
     * Permet d'arroser l'arbre sur lequel le robot est
     */
    // Vérifie si l'on a assez d'eau pour arroser
    if(this->getCapacity() <= 0){
        std::cout << "Le robot n'a plus d'eau" << std::endl;
        return;
    }

    // Récupère l'arbre sur lequel le robot est
    std::cout << "Le robot arrose l'arbre en position : (" <<this->getDesiredPose()[0]<<";"<<this->getDesiredPose()[1]<<")"<< std::endl;
    Arbre *arbre = (Arbre *) this->getLocalMap()[this->getPositionObjectifEnLocal()[0]][this->getPositionObjectifEnLocal()[1]];
    arbre->arroser(); // On arrose l'arbre
    this->setCapacity(this->getCapacity() - 1); // On enlève de l'eau au robot
    this->setActualManeuver(Robot::ActualManeuver::Idle); // On met le robot en mode Idle
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
        for(int x=0;x<getLocalMap().size();x++) {
            for (int y = 0; y < getLocalMap()[x].size() ; y++) {
                if (getLocalMap()[x][y]->getNom() == "A") { // Si c'est un arbre
                    Arbre *arbre = (Arbre *) getLocalMap()[x][y];
                    if (!arbre->getIsWatered()) { // Si l'arbre n'est pas encore arrosé
                        this->setDesiredPose((float) arbre->getPosition()[0],(float) arbre->getPosition()[1], 0);
                        this->setPositionObjectifEnLocal(x, y);
                        this->setActualManeuver(Robot::ActualManeuver::Mouvement);
                        return;
                    }
                }
            }
        }
        goto noTreeToWater; // On saute le code suivant // TODO : juste pour le debug à enlever
        // Aucun arbre a arrosé n'a été trouvé
        // Scanner l'environnement pour vérifier s'il y a un arbre à arroser avec un plus grand rayon
        /*if (this->getLocalMap().size() < 5) {
            this->scan(env, 2); // On scan avec un rayon de 2 (avant on était à 1)
            this->priseDecision(env);
        }
        else {*/noTreeToWater:
            // Si on a déjà scanné avec un rayon de 5 et qu'on a rien trouvé
            // On vérifie si on a un arbre à arroser avec un rayon de 1
            this->scan(env, 1); // On repart sur un scan de rayon 1
            for (int x = 0; x < getLocalMap().size() ; x++) {
                for (int y = 0; y < getLocalMap()[x].size() ; y++) {
                    if (getLocalMap()[x][y]->getNom() == "A") { // Si c'est un arbre
                        this->setActualManeuver(Robot::ActualManeuver::Idle); // Ne bouge pas
                        return;
                    }
                }
            }
            // On a pas du tout trouvé d'arbre
            // donc on se déplace aléatoirement
            this->setActualManeuver(Robot::ActualManeuver::Mouvement);
            std::mt19937 gen(Environment::genereteSeed());
            std::uniform_int_distribution<unsigned> distrib(1,
                                                            std::max(env.getSize()[0], env.getSize()[1]) -
                                                            1);
            this->setDesiredPose(distrib(gen), distrib(gen), 0);
            return;
        //}
    }
}

void RobotArroseur::action(Environment &env) {
    /*
     * Permet de mettre en place l'action d'arrosage
     * l'action est la suivante : si on est sur un arbre, on l'arrose
     * sinon on se déplace jusqu'à trouver un arbre à arroser
     */

    // Vérifie s'il y a déjà une pose disérer à atteindre
    if(this->getActualManeuver() == Robot::ActualManeuver::Mouvement) { // une direction est déjà définie
        float margin = 1.1; // marge d'erreur pour la pose
        float xd = this->getDesiredPose()[0];
        float yd = this->getDesiredPose()[1];
        auto x = (float)this->getPosition()[0];
        auto y = (float)this->getPosition()[1];
        if(xd - margin <= x && x <= xd + margin && yd - margin <= y && y <= yd + margin) {
            // Si on est sur la pose désirée
            this->setActualManeuver(Robot::ActualManeuver::SpecialAction); // On met le robot en mode arrosage
        }
        else
        // On se déplace jusqu'à la pose désirée
            this->moveCinematique(xd, yd, this->getSpeed(), env.getDeltaT());
        return;
    }
    else if(this->getActualManeuver() == Robot::ActualManeuver::SpecialAction) { // une direction est déjà définie
        this->arroser();
        return;
    }
    else if(this->getActualManeuver() == Robot::ActualManeuver::Idle) { // aucune direction n'est définie
        return; // On ne fait rien
    }
    else { // Une action non définie est demandée (erreur)
        std::cerr << "Erreur: action non définie" << std::endl;
        return;
    }
}
