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

void RobotArroseur::arroser(Environment &env) {
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

    // Vériie que le robot est sur un arbre
    if(env.getMap()[(int)this->diseriedPose[0]][(int)this->diseriedPose[1]]->getNom() == "A"){
        std::cerr << "Erreur : le robot n'est pas sur un arbre" << std::endl;
        return;
    }
    else // Si c'est le cas
    {
        Arbre *arbre = (Arbre *) env.getMap()[(int)this->diseriedPose[0]][(int)this->diseriedPose[1]];
        arbre->arroser(); // On arrose l'arbre
        this->setCapacity(this->getCapacity() - 1); // On enlève de l'eau au robot
        this->setActualManeuver(Robot::ActualManeuver::Idle); // On met le robot en mode Idle
    }
}

void RobotArroseur::priseDecision(Environment &env) {
    /*
     * Permet de metter en place la stratégie d'arrosage
     * la stratégie est la suivante : si il y a un arbre à arroser, on l'arrose
     * sinon on se déplace jusqu'à trouver un arbre à arroser
     */

    // Si le robot est en mode Idle ou Mouvement alors on regarde son environnement pour une potentielle action
    if(this->getActualManeuver() == Robot::ActualManeuver::Idle || this->getActualManeuver() == Robot::ActualManeuver::Mouvement)
    {
        // On vérifie si on a assez d'eau pour arroser
        if (this->getCapacity() <= 0) { // TODO : Mettre en place un système de recharge
            std::cout << "Le robot n'a plus d'eau" << std::endl;
            return;
        }
        else {
            // On cherche un arbre sur la carte local
            for(int i=0;i< this->getLocalMap().size();i++){
                for (int j = 0; j < this->getLocalMap().size(); j++) {
                    if(this->getLocalMap()[i][j]->getNom() == "A"){
                        // Si on trouve un arbre
                        // On regarde si l'arbre n'est pas déjà arrosé
                        Arbre *arbre = (Arbre *) this->getLocalMap()[i][j];
                        if(!(arbre->getIsWatered())){ // Si l'arbre n'est pas arrosé
                            // On se déplace jusqu'à l'arbre
                            this->setDesiredPose((float)arbre->getPosition()[0],(float)arbre->getPosition()[1],0); // On définit la pose désirée
                            this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On met le robot en mode mouvement
                            return;
                        }
                    }
                }
            }
            // Si on ne trouve pas d'arbre à arroser
            if(this->getLocalMap().size() < 5) // On augmente le rayon de recherche
            {
                this->scan(env,2);  // On augmente le rayon de la carte local
                this->priseDecision(env); // Et on recommence la prise de décision
            }
            else{
                // Si on ne trouve pas d'arbre à arroser
                // On se déplace aléatoirement
                this->moveAleatoire(env);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On met le robot en mode mouvement
                return;
            }
        }
    }
    // si le robot est dans un autre mode alors on ne fait rien (on attend que cela soit fini)
    else {
        this->move(0,0); // On arrête le robot
        return;
    }
}

void RobotArroseur::action(Environment &env) {
    /*
     * Permet de mettre en place l'action d'arrosage
     * l'action est la suivante : si on est sur un arbre, on l'arrose
     * sinon on se déplace jusqu'à trouver un arbre à arroser
     */
    this->move(5,5);
    return;

    // Vérifie s'il y a déjà une pose disérer à atteindre
    if(this->getActualManeuver() == Robot::ActualManeuver::Mouvement) { // une direction est déjà définie
        float margin = 0.01; // marge d'erreur pour la pose
        float xd = this->getDesiredPose()[0];
        float yd = this->getDesiredPose()[1];
        auto x = (float)this->getPose()[0];
        auto y = (float)this->getPose()[1];
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
        this->arroser(env);
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
