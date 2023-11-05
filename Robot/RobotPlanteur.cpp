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

void RobotPlanteur::priseDecision(Environment &env) {
    /*
     * Permet de prendre une décision contenue de l'environnement et de la spécificité du robot
     */

    // En fonction de l'état du robot, on va prendre une décision
    if(this->getActualManeuver()==Robot::ActualManeuver::Idle || this->getActualManeuver()==Robot::ActualManeuver::Mouvement){
        // Vérifie que l'on a des graines
        if(this->getCapacity()<=0){
            // TODO : si le robot n'a pas de graine, il va chercher des graines
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
                    if(this->isFreeZoneToPlant(env,i,j)){ // Si une zone de plantation est disponible
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
            // On regarde si la case à droite est libre
            if(this->getLocalMap()[this->getPosition()[0]+1][this->getPosition()[1]]->getNom()=="_"){
                // On enregistre la position de la case à droite
                this->setDesiredPose(this->getPosition()[0]+1,this->getPosition()[1],0);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
                return;
            }
            // On regarde si la case en bas est libre
            else if(this->getLocalMap()[this->getPosition()[0]][this->getPosition()[1]+1]->getNom()=="_"){
                // On enregistre la position de la case en bas
                this->setDesiredPose(this->getPosition()[0],this->getPosition()[1]+1,0);
                this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
                return;
            }
            // Si on arrive ici, c'est que les cases à droite et en bas ne sont pas libres
            // On retourne à la case de départ
            this->setDesiredPose(1,1,0);
            this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On passe en mode mouvement
            return;
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
    return;
}

bool RobotPlanteur::isFreeZoneToPlant(Environment &env, int x, int y) {
    /*
     * Permet de vérifier si la zone de plantation est libre
     */
    // Vérifie que les paramètres sont bien dans la map
    if(x<1 || x>env.getMap().size() || y<1 || y>env.getMap().size()){
        std::cerr << "Erreur : les paramètres ne sont pas dans la map" << std::endl;
        return false;
    }
    // Vérifie autour de la zone donnée en paramètre avec un rayon de 1 s'il y a un obstacle
    for(int i=x-1; i<=x+1; i++){
        for(int j=y-1; j<=y+1; j++){
            if(env.getMap()[i][j]->getNom()!="_"){
                return false;
            }
        }
    }
    return true;
}

