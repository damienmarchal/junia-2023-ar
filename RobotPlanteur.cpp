#include "RobotPlanteur.h"
RobotPlanteur::RobotPlanteur(int id, Environment& map, int case_x, int case_y) : Robot(id,map,case_x,case_y) {

}
void RobotPlanteur::planter(Environment& map) {
    //par défaut après avoir planter le robot se décale sur la droite
    if (this->case_x <= map.size_x - 2 && map.map_etat[this->case_y][this->case_x + 1] == Etat::libre) {
        map.map_etat[this->case_y][this->case_x] = Etat::arbre;
        //ajouter un déplacement d'une case vers la droite 
    }
    //si ce c'est pas possible, il monte
    else if (this->case_y >= 1 && map.map_etat[this->case_y - 1][this->case_x] == Etat::libre) {
        map.map_etat[this->case_y][this->case_x] = Etat::arbre;
        //ajouter un déplacement d'un cran vers le haut
    }
    //si ce n'est pas possible, il va vers la gauche
    else if (this->case_x >= 1 && map.map_etat[this->case_y][this->case_x - 1] == Etat::libre) {
        map.map_etat[this->case_y][this->case_x] = Etat::arbre;
        //ajouter un déplacement d'un cran vers la droite
    }
    //si ce n'est pas possible, il descent
    else if (this->case_y <= map.size_y - 2 && map.map_etat[this->case_y + 1][this->case_x] == Etat::libre) {
        map.map_etat[this->case_y][this->case_x] = Etat::arbre;
        //ajouter un déplacement d'un cran vers la droite
    }
    //si aucun de ces mouvement n'est possible alors le robot ne peut pas planter
    else {
        std::cout << "impossible de planter ici" << std::endl;
    }
}