#include "RobotPlanteur.h"
RobotPlanteur::RobotPlanteur(int id, Environment& map, int pos_x, int pos_y) : Robot(id,map,pos_x,pos_y) {

}
void RobotPlanteur::planter(Environment& map) {
    //par défaut après avoir planter le robot se décale sur la droite
    if (this->pos_x <= map.size_x - 2 && map.map_etat[this->pos_y][this->pos_x + 1] == Etat::libre) {
        map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
        map.map_etat[this->pos_y][this->pos_x + 1] = Etat::robot;
        this->pos_x = this->pos_x + 1;
    }
    //si ce c'est pas possible, il monte
    else if (this->pos_y >= 1 && map.map_etat[this->pos_y - 1][this->pos_x] == Etat::libre) {
        map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
        map.map_etat[this->pos_y - 1][this->pos_x] = Etat::robot;
        this->pos_y = this->pos_y - 1;
    }
    //si ce n'est pas possible, il va vers la gauche
    else if (this->pos_x >= 1 && map.map_etat[this->pos_y][this->pos_x - 1] == Etat::libre) {
        map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
        map.map_etat[this->pos_y][this->pos_x - 1] = Etat::robot;
        this->pos_x = this->pos_x - 1;
    }
    //si ce n'est pas possible, il descent
    else if (this->pos_y <= map.size_y - 2 && map.map_etat[this->pos_y + 1][this->pos_x] == Etat::libre) {
        map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
        map.map_etat[this->pos_y + 1][this->pos_x] = Etat::robot;
        this->pos_y = this->pos_y + 1;
    }
    //si aucun de ces mouvement n'est possible alors le robot ne peut pas planter
    else {
        std::cout << "impossible de planter ici" << std::endl;
    }
}