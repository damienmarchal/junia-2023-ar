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
void RobotPlanteur::planter(Environment &env, int x, int y) {
    /*
     * Permet de planter un arbre
     */
    // Vérifier que le robot a des graines
    if(this->getCapacity()<=0){
        std::cerr << "Erreur : le robot n'a pas de graines" << std::endl;
        return;
    }
    else {
        if (this->isFreeZoneToPlant(env, x, y)) { // Vérifie que la zone est libre
            if(env.addArbre(x, y) ==1)
                this->setCapacity(this->getCapacity()-1); // On enlève une graine si l'on a réussi à planter
        }
        else {
            return;
        }
    }
}

void RobotPlanteur::action(Environment &env) {
    /*
     * Permet de faire l'action du robot en fonction de son mode
     */
    switch (this->getActualManeuver()) {
        case ActualManeuver::Mouvement:
            if(Environment::CalculDistance((this->getPose()[0]),(this->getPose()[1]),(this->getDesiredPose()[0]),(this->getDesiredPose()[1]))>=.51)
                this->moveCinematique(this->getDesiredPose()[0],this->getDesiredPose()[1],this->getSpeed(),env.getDeltaT());
            else
                this->setActualManeuver(Robot::ActualManeuver::Idle);
            break;

        case ActualManeuver::SpecialAction:
            this->planter(env,(int)this->getDesiredPose()[0],(int)this->getDesiredPose()[1]); // TODO : vérifier que la position est bien la bonne
            this->setActualManeuver(Robot::ActualManeuver::Idle);
            break;

        case ActualManeuver::Idle:
            this->setSpeed(0);// On arrête le robot
            break;
    }
}

void RobotPlanteur::priseDecision(Environment &env) {
    /*
     * Permet de prendre une décision contenue de l'environnement et de la spécificité du robot
     */

    // En fonction de l'état du robot, on va prendre une décision
    if(this->getActualManeuver()==Robot::ActualManeuver::Idle || this->getActualManeuver()==Robot::ActualManeuver::Mouvement){
        // Vérifie que l'on a des graines
        if(this->getCapacity()<=0){
            this->setDesiredPose(1,1,0); // On retourne à la case de départ
            this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
            return;
        }
        else{ // Si l'on a des graines
            /*
             * La stratégie de base qui pourra ensuite être améliorée est la suivante :
             * - On regarde si une zone de plantation est disponible autour de l'arbre (rayon de 1)
             * - Si oui, on plante un arbre à cet endroit
             * - Si non, on se déplace pour trouver une zone de plantation
             */
            // On regarde si une zone de plantation est disponible
            for(int i=0;i<this->getLocalMap().size();i++){
                for(int j=0;j<this->getLocalMap().size();j++){
                    if(this->isFreeZoneToPlant(env,this->getLocalMap()[i][j]->getPosition()[0],this->getLocalMap()[i][j]->getPosition()[1])){ // Si une zone de plantation est disponible
                        // Enregistrer la position de la zone de plantation
                        this->setDesiredPose( this->getLocalMap()[i][j]->getPosition()[0], this->getLocalMap()[i][j]->getPosition()[1],0);
                        this->setActualManeuver(Robot::ActualManeuver::SpecialAction); // On passe en mode plantation
                        return;
                    }
                }
            }
            // Si on arrive ici, c'est qu'aucune zone de plantation n'est disponible
            /*
             * Dans ce cas la stratégie est de se déplacer vers une zone de plantation
             * La stratégie de base est de se déplacer d'une case vers la droite
             * si la case est libre, sinon de se déplacer d'une case vers le bas
             * sinon on retourne à la case de départ ( 1,1 ) c'est là on l'on aura la station de recharge
             */
            // On doit déjà avoir un emplacement car on est en  déplacement
            if(this->getActualManeuver()==Robot::ActualManeuver::Mouvement){ return; } // On ne fait rien de plus car on est déjà en train de se déplacer
            // sinon on effectue la sratégie de base

            // On regarde si la case à droite est libre
            if(env.getMap()[this->getPose()[0]][this->getPose()[1]+1]->getNom()=="_"){
                // On enregistre la position de la case à droite
                this->setDesiredPose(this->getPose()[0],this->getPose()[1]+1,0);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
                return;
            }
            // On regarde si la case en bas est libre
            else if(env.getMap()[this->getPose()[0]+1][this->getPose()[1]]->getNom()=="_"){
                // On enregistre la position de la case en bas
                this->setDesiredPose(this->getPose()[0]+1,this->getPose()[1],0);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
                return;
            }
            // Si on arrive ici, c'est que les cases à droite et en bas ne sont pas libres
            // On retourne à la case de départ
            else{
                this->setDesiredPose(1,1,0);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
                return;
            }
        }
    }
    else if(this->getActualManeuver()==Robot::ActualManeuver::SpecialAction){
        // Vérifier que le robot peut bien faire une action spéciale
        if(this->getCapacity()<=0 || this->isFreeZoneToPlant(env,this->getDesiredPose()[0],this->getDesiredPose()[1])){
            std::cerr << "Erreur : le robot ne peux pas faire d'action spécial" << std::endl;
            this->setActualManeuver(Robot::ActualManeuver::Idle);
            return;
        }
        return; // On ne fait rien car on est déjà en train de faire une action spéciale
    }
    else{
        std::cerr << "Erreur : le robot n'est pas dans un état connu" << std::endl;
    }
}

bool RobotPlanteur::isFreeZoneToPlant(Environment &env, int x, int y) {
    /*
     * Permet de vérifier si la zone de plantation est libre
     */
    // Vérifie que les paramètres sont bien dans la map
    if(x<0 || x>=env.getSize()[0] || y<0 || y>=env.getSize()[1]){
        //std::cerr << "Erreur : les paramètres ne sont pas dans la map" << std::endl;
        return false;
    }
    // Vérifie autour de la zone donnée en paramètre avec un rayon de 1 s'il y a un obstacle
    for(int i=x-1; i<=x+1; i++){
        for(int j=y-1; j<=y+1; j++){
            // Vérifie que les paramètres sont bien dans la map
            if(i<0 || i>=env.getSize()[0] || j<0 || j>=env.getSize()[1]){
               // std::cerr << "Erreur : les paramètres ne sont pas dans la map" << std::endl;
                continue;
            }
            if(env.getMap()[i][j]->getNom()=="A"){ // Si il y a un arbre
                return false; // On retourne faux
            }
        }
    }
    if(env.getMap()[x][y]->getNom()=="_") // Si à la position donnée en paramètre il y a rien
        return true; // On retourne vrai
    else // S'il y a un obstacle
        return false; // On retourne faux
}

